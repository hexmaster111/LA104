struct TSetting // Cute little struct to hold the settings
{
    const char *name;
    int value;
    int min;
    int max;
    enum TFormat{hex, dec} format;
};