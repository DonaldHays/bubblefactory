#include "palette.h"
#include "gb.h"

void paletteSetLevel(GBUInt8 level) {
    if(level == 0) {
        gbPaletteSet(gbBackgroundPaletteRegister, gbShadeWhite, gbShadeWhite, gbShadeWhite, gbShadeWhite);
        gbPaletteSet(gbObject0PaletteRegister, gbShadeWhite, gbShadeWhite, gbShadeWhite, gbShadeWhite);
        gbPaletteSet(gbObject1PaletteRegister, gbShadeWhite, gbShadeWhite, gbShadeWhite, gbShadeWhite);
    } else if(level == 1) {
        gbPaletteSet(gbBackgroundPaletteRegister, gbShadeLightGray, gbShadeWhite, gbShadeWhite, gbShadeWhite);
        gbPaletteSet(gbObject0PaletteRegister, gbShadeLightGray, gbShadeWhite, gbShadeWhite, gbShadeWhite);
        gbPaletteSet(gbObject1PaletteRegister, gbShadeLightGray, gbShadeWhite, gbShadeWhite, gbShadeWhite);
    } else if(level == 2) {
        gbPaletteSet(gbBackgroundPaletteRegister, gbShadeDarkGray, gbShadeLightGray, gbShadeWhite, gbShadeWhite);
        gbPaletteSet(gbObject0PaletteRegister, gbShadeDarkGray, gbShadeWhite, gbShadeWhite, gbShadeWhite);
        gbPaletteSet(gbObject1PaletteRegister, gbShadeDarkGray, gbShadeLightGray, gbShadeWhite, gbShadeWhite);
    } else if(level == 3) {
        gbPaletteSet(gbBackgroundPaletteRegister, gbShadeBlack, gbShadeDarkGray, gbShadeLightGray, gbShadeWhite);
        gbPaletteSet(gbObject0PaletteRegister, gbShadeBlack, gbShadeLightGray, gbShadeWhite, gbShadeWhite);
        gbPaletteSet(gbObject1PaletteRegister, gbShadeBlack, gbShadeDarkGray, gbShadeWhite, gbShadeWhite);
    } else {
        gbLogUInt8(level);
        gbFatalError("unrecognized level");
    }
}

void paletteSetPaused() {
    gbPaletteSet(gbBackgroundPaletteRegister, gbShadeBlack, gbShadeBlack, gbShadeDarkGray, gbShadeLightGray);
    gbPaletteSet(gbObject0PaletteRegister, gbShadeBlack, gbShadeDarkGray, gbShadeLightGray, gbShadeLightGray);
    gbPaletteSet(gbObject1PaletteRegister, gbShadeBlack, gbShadeBlack, gbShadeLightGray, gbShadeLightGray);
}
