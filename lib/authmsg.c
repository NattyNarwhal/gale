#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "gale/all.h"

static struct gale_message *sign(struct gale_id *id,struct gale_message *in,
                                 int tweak) 
{
	struct gale_message *out = NULL;
	struct gale_data sig;
	if (tweak)
		_auth_sign(id,in->data,&sig);
	else
		auth_sign(id,in->data,&sig);
	if (sig.p) {
		int len = armor_len(sig.l);
		out = new_message();
		out->cat = gale_text_dup(in->cat);
		out->data.l = 16 + len + in->data.l;
		out->data.p = gale_malloc(out->data.l);
		strcpy(out->data.p,"Signature: g2/");
		armor(sig.p,sig.l,out->data.p + 14);
		strcpy(out->data.p + 14 + len,"\r\n");
		memcpy(out->data.p + 16 + len,in->data.p,in->data.l);
		gale_free(sig.p);
	}

	if (!out) addref_message(out = in);
	return out;
}

struct gale_message *sign_message(struct gale_id *id,struct gale_message *in) {
	return sign(id,in,0);
}

struct gale_message *_sign_message(struct gale_id *id,struct gale_message *in) {
	return sign(id,in,1);
}

struct gale_message *encrypt_message(int num,struct gale_id **id,
                                     struct gale_message *in) 
{
	struct gale_message *out = NULL;
	struct gale_data cipher;
	int i;

	for (i = 0; i < num; ++i)
		if (!auth_id_public(id[i])) {
			gale_alert(GALE_WARNING,"cannot encrypt without key",0);
			return NULL;
		}

	auth_encrypt(num,id,in->data,&cipher);

	if (!cipher.p) return NULL;

	out = new_message();
	out->cat = gale_text_dup(in->cat);
	out->data.p = gale_malloc(out->data.l = cipher.l + 16);
	strcpy(out->data.p,"Encryption: g2\r\n");
	memcpy(out->data.p + 16,cipher.p,cipher.l);
	gale_free(cipher.p);

	return out;
}

struct gale_id *verify_message(struct gale_message *in) {
	const char *ptr = in->data.p,*end;
	const char *dptr,*dend = in->data.p + in->data.l;
	struct gale_id *id = NULL;

	for (end = ptr; end < dend && *end != '\r'; ++end) ;
	dptr = end + 1;
	if (dptr < dend && *dptr == '\n') ++dptr;

	if (end == dend) {
		id = NULL;
	} else if (!strncasecmp(in->data.p,"Signature: g2/",14)) {
		struct gale_data data,sig;

		ptr += 14;
		sig.l = dearmor_len(end - ptr);
		sig.p = gale_malloc(sig.l);
		dearmor(ptr,end - ptr,sig.p);

		data.l = dend - dptr;
		data.p = (byte *) dptr;

		auth_verify(&id,data,sig);
		gale_free(sig.p);
	}

	return id;
}

struct gale_id *decrypt_message(struct gale_message *in,
                                struct gale_message **out) 
{
	const char *ptr = in->data.p,*end;
	const char *dptr,*dend = in->data.p + in->data.l;
	struct gale_id *id = NULL;
	*out = in;

	for (end = ptr; end < dend && *end != '\r'; ++end) ;
	dptr = end + 1;
	if (dptr < dend && *dptr == '\n') ++dptr;

	if (end == dend)
		*out = in;
	else if (!strncasecmp(ptr,"Encryption: g2",14)) {
		struct gale_data cipher,plain;

		*out = NULL;
		cipher.p = (byte *) dptr;
		cipher.l = dend - dptr;
		auth_decrypt(&id,cipher,&plain);

		if (id) {
			*out = new_message();
			(*out)->cat = gale_text_dup(in->cat);
			(*out)->data.p = plain.p;
			(*out)->data.l = plain.l;
		}
	}

	if (*out) addref_message(*out);
	return id;
}
