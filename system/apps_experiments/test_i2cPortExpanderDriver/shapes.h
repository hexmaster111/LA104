struct TSetting // Cute little struct to hold the settings
{
    const char *name;
    int value;
    int min;
    int max;
};

static const char CShapes_sel_left[] =
    "\x0e"
    "              "
    "              "
    "              "
    "              "
    "  ..........  "
    " ............ "
    ".............."
    "..............";

static const char CShapes_sel_right[] =
    "\x0e"
    ".............."
    ".............."
    " ............ "
    "  ..........  "
    "              "
    "              "
    "              "
    "              ";
static const char CShapes_check_box[] =
    "\x0e"
    "              "
    "    .......   "
    "    .     .   "
    "    .     .   "
    "    .     .   "
    "    .     .   "
    "    .......   "
    "              ";
static const char CShapes_check_on[] =
    "\x0e"
    "       ..     "
    "        ..    "
    "         ..   "
    "          ..  "
    "        ...   "
    "     ....     "
    "   ...        "
    "              ";

static const char CShapes_dot[] =
    "\x0e"
    "              "
    "     ...      "
    "    .....     "
    "   .......    "
    "   .......    "
    "   .......    "
    "    .....     "
    "     ...      "
    "              ";

static const char CShapes_dotout[] =
    "\x0e"
    "    .....     "
    "   ..---..    "
    "  ..-----..   "
    "  .-------.   "
    "  .-------.   "
    "  .-------.   "
    "  ..-----..   "
    "   ..---..    "
    "    .....     ";

static const char CShapes_degree[] =
    "\x0e"
    "              "
    "              "
    "              "
    "   ..         "
    "  .  .        "
    "  .  .        "
    "   ..         ";
