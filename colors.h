static const char norm_fg[] = "#C0C0C0";
static const char norm_bg[] = "#000000";
static const char norm_border[] = "#404040";

static const char sel_fg[] = "#FFFFFF";
static const char sel_bg[] = "#404040";
static const char sel_border[] = "#FFFFFF";

static const char hid_fg[] = "#FFFFFF";
static const char hid_bg[] = "#000000";
static const char hid_border[] = "#404040";
static const char col_urgborder[]   = "#ff0000";

static const char *colors[][3]      = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
    [SchemeHid]  = { hid_fg,      hid_bg,    hid_border },  // Tab Colorschemes
	[SchemeUrg]  = { sel_fg,      sel_bg,    col_urgborder },
};
