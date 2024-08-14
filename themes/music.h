static const char norm_fg[] = "#79dde9";
static const char norm_bg[] = "#110f1e";
static const char norm_border[] = "#549aa3";

static const char sel_fg[] = "#79dde9";
static const char sel_bg[] = "#076D8D";
static const char sel_border[] = "#79dde9";

static const char urg_fg[] = "#79dde9";
static const char urg_bg[] = "#BC413B";
static const char urg_border[] = "#BC413B";

static const char *colors[][3]      = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
    [SchemeHid] =  { urg_fg,      urg_bg,    urg_border },  // Tab Colorschemes (awesomebar)
    [SchemeUrg] =  { urg_fg,      urg_bg,    urg_border },
};

static const char *wallpaper[] = {"feh", "--no-fehbg", "--bg-fill", "/home/jayar/.config/wall/music.jpg", NULL };
