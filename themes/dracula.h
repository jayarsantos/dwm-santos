static const char norm_fg[]       = "#f8f8f2";
static const char norm_bg[]       = "#282a36";
static const char norm_border[] = "#404040";

static const char sel_bg[]       = "#a272a4";
static const char sel_border[]       = "#644475";
static const char sel_fg[]       = "#f8f8f2";

static const char hid_border[]       = "#f8f8f2";
static const char hid_bg[]       = "#282a36";
static const char hid_fg[]        = "#bf93f9";

static const char col_urgborder[]   = "#ff0000";

static const char *colors[][3]      = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
    [SchemeHid]  = { hid_fg,      hid_bg,    hid_border },  // Tab Colorschemes
	[SchemeUrg]  = { sel_fg,      sel_bg,    col_urgborder },
};

