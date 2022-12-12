/* Fontconfig match
 * January 28, 2022 */
/* Compile with -lfontconfig */
#include <stdio.h>
#include <stdlib.h>
#include <fontconfig/fontconfig.h>

int main(int argc, char **argv) {
	FcConfig *conf;
	FcFontSet *fs;
	FcObjectSet *os = 0;
	FcPattern *pat;
	FcResult result;

	if (argc < 2) {
		fprintf(stderr, "USAGE: %s \"Font name\"\n", argv[0]);
		return 1;
	}

	conf = FcInitLoadConfigAndFonts();

	if (!(pat = FcNameParse((FcChar8*)argv[1]))) {
		fprintf(stderr, "Could not find pattern\n");
		return 2;
	}
	FcConfigSubstitute(conf, pat, FcMatchPattern);
	FcDefaultSubstitute(pat);

	fs = FcFontSetCreate();
	os = FcObjectSetBuild(FC_FAMILY, FC_STYLE, FC_FILE, (char*)0);

	FcFontSet *font_patterns;
	font_patterns = FcFontSort(conf, pat, FcTrue, 0, &result);

	if (!font_patterns || font_patterns->nfont == 0) {
		fprintf(stderr, "Fontconfig could find no fonts\n");
		return 3;
	}

	FcPattern *font_pattern;
	font_pattern = FcFontRenderPrepare(conf, pat, font_patterns->fonts[0]);
	if (font_pattern)
		FcFontSetAdd(fs, font_pattern);
	else {
		fprintf(stderr, "Could not prepare font\n");
		return 4;
	}

	FcFontSetSortDestroy(font_patterns);
	FcPatternDestroy(pat);

	if (fs) {
		if (fs->nfont > 0) {
			FcValue v;
			FcPattern *font;

			font = FcPatternFilter(fs->fonts[0], os);
			FcPatternGet(font, FC_FILE, 0, &v);
			const char *path = (char *)v.u.f;
			printf("Path: %s\n", path);
			FcPatternDestroy(font);
		}
		FcFontSetDestroy(fs);
	}

	if (os)
		FcObjectSetDestroy(os);

	return 0;
}

