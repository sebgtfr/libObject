
#include <stdio.h>
#include "Objects/String.h"

#ifdef __cplusplus

using namespace					Objects;

#endif

int								main(void)
{
	char const * const			name = "Sébastien";
	char const * const			john = "John";
	String						strName = String_ctor(name);
	String						copyName = String_ctorCopy(&strName);
	String						copy2Name = String_ctor(NULL);
	String						copy3Name = String_ctor(NULL);
	String						copy4Name = String_ctor(NULL);

	String_eq(&copy3Name, String_assign(&copy2Name, String_rawData(&strName)));
	String_concatString(&copy4Name, String_concat(&strName, ", J'ai 15 € !"));

	size_t						e = String_find(&copy4Name, UnicodeChar_ctor("é"));
	size_t						euro = String_find(&copy4Name, UnicodeChar_ctor("€"));

	(void)printf("Dans la phrase : \"%s\" le caratère '",
				 String_rawData(&copy4Name));
	UnicodeChar_print(String_unicodeAt(&copy4Name, e));
	(void)printf("' commence en mémoire en position %lu et le caratère '", e);
	UnicodeChar_print(String_unicodeAt(&copy4Name, euro));
	(void)printf("' commence en mémoire en position %lu\n", euro);

	(void)printf("\"%s\" == \"%s\" est %i\n",
				 String_rawData(&strName), String_rawData(&copy4Name),
				 CAST_BOOL(String_compare(&strName, &copy4Name) == 0));
	(void)printf("\"%s\" == \"%s\" est %i\n",
				 String_rawData(&copy3Name), name,
				 CAST_BOOL(String_cmp(&copy3Name, name) == 0));
	(void)printf("\"%s\" <= \"%s\" est %i\n",
				 String_rawData(&copy3Name), name,
				 CAST_BOOL(String_cmp(&copy3Name, name) <= 0));
	(void)printf("\"%s\" >= \"%s\" est %i\n",
				 String_rawData(&copy3Name), name,
				 CAST_BOOL(String_cmp(&copy3Name, name) >= 0));
	(void)printf("\"%s\" != \"%s\" est %i\n",
				 String_rawData(&copy3Name), name,
				 CAST_BOOL(String_cmp(&copy3Name, name) != 0));
	(void)printf("\"%s\" == \"%s\" est %i\n",
				 String_rawData(&copy3Name), String_rawData(&copy4Name),
				 CAST_BOOL(String_compare(&copy3Name, &copy4Name) == 0));
	(void)printf("\"%s\" < \"%s\" est %i\n",
				 String_rawData(&copy3Name), String_rawData(&copy4Name),
				 CAST_BOOL(String_compare(&copy3Name, &copy4Name) < 0));
	(void)printf("\"%s\" > \"%s\" est %i\n",
				 String_rawData(&copy3Name), String_rawData(&copy4Name),
				 CAST_BOOL(String_compare(&copy3Name, &copy4Name) > 0));
	(void)printf("\"%s\" > \"%s\" est %i\n",
				 String_rawData(&copy3Name), NULL,
				 CAST_BOOL(String_cmp(&copy3Name, NULL) > 0));
	(void)printf("\"%s\" < \"%s\" est %i\n",
				 String_rawData(&copy3Name), NULL,
				 CAST_BOOL(String_cmp(&copy3Name, NULL) < 0));
	(void)printf("\"%s\" == \"%s\" est %i\n",
				 String_rawData(&copy3Name), NULL,
				 CAST_BOOL(String_cmp(&copy3Name, NULL) == 0));
	String_assign(&copy3Name, NULL);
	(void)printf("\"%s\" == \"%s\" est %i\n",
				 String_rawData(&copy3Name), NULL,
				 CAST_BOOL(String_cmp(&copy3Name, NULL) == 0));
	String_assign(&strName, john);

	String						johnlc = String_lowercase(&strName);
	String						johnuc = String_uppercase(&strName);;

	String						sub = String_substrToUnicode(&copy4Name, 0,
															 UnicodeChar_ctor("n"));
	String						rev = String_reverse(&sub);

	String_eq(&copy4Name, &rev);

	String_dtor(&sub);
	String_dtor(&rev);

	(void)printf("reverse : %s\n", String_rawData(&copy4Name));

	_OBJECTS_UNICODE_STRING_ITERATOR_ revIt = String_unicodeEnd(&copy4Name);

	while (!Unicode_String_Iterator_eq((revIt = Unicode_String_Iterator_prev(revIt)),
									   String_unicodeBegin(&copy4Name)))
		UnicodeChar_print(Unicode_String_Iterator_content(revIt));
	UnicodeChar_print(Unicode_String_Iterator_content(revIt));
	(void)printf("\n");

	String_dtor(&strName);
	String_dtor(&copyName);
	String_dtor(&copy2Name);
	String_dtor(&copy3Name);
	String_dtor(&copy4Name);
	String_dtor(&johnlc);
	String_dtor(&johnuc);
	return 0;
}
