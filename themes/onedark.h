static const char norm_fg[]      = "#ABB2BF";
static const char norm_bg[]      = "#282C34";
static const char norm_border[]  = "#ABB2BF";

static const char sel_fg[]       = "#c678DD";
static const char sel_bg[]       = "#282C34";
static const char sel_border[]   = "#E06C75";

static const char hid_fg[]       = "#282C34";
static const char hid_bg[]       = "#ABB2BF";
static const char hid_border[]   = "#E06C75";

static const char col_urgborder[]  = "#ff0000";

static const char *colors[][3]      = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
    [SchemeHid]  = { hid_fg,      hid_bg,    hid_border },  // Tab Colorschemes
	[SchemeUrg]  = { sel_fg,      sel_bg,    col_urgborder },
};

