#ifndef CellPad_h
#define CellPad_h

enum cellPadKeys : int {
	PAD_NOKEY = 0,
	PAD_CROSS = CELL_PAD_CTRL_CROSS,
	PAD_CIRCLE = CELL_PAD_CTRL_CIRCLE,
	PAD_SQUARE = CELL_PAD_CTRL_SQUARE,
	PAD_TRIANGLE = CELL_PAD_CTRL_TRIANGLE,
	PAD_L1 = CELL_PAD_CTRL_L1,
	PAD_R1 = CELL_PAD_CTRL_R1,
	PAD_L3 = CELL_PAD_CTRL_L3,
	PAD_R3 = CELL_PAD_CTRL_R3,
	PAD_L2 = CELL_PAD_CTRL_L2,
	PAD_R2 = CELL_PAD_CTRL_R2,
	PAD_UP = CELL_PAD_CTRL_UP,
	PAD_DOWN = CELL_PAD_CTRL_DOWN,
	PAD_LEFT = CELL_PAD_CTRL_LEFT,
	PAD_RIGHT = CELL_PAD_CTRL_RIGHT,
	PAD_MAX = 15,
};

struct cellPadButtonData {
	int btnData;
	int btnDigital;
};

extern CellPadData _pdPad;
extern cellPadButtonData pdPadBtn[PAD_MAX];

inline bool PadDown(int button, int digit = CELL_PAD_BTN_OFFSET_DIGITAL1) {
	return _pdPad.button[digit] & (button);
}

inline void PadInit() {
	pdPadBtn[0].btnData = 0;
	pdPadBtn[1].btnData = CELL_PAD_CTRL_CROSS;
	pdPadBtn[2].btnData = CELL_PAD_CTRL_CIRCLE;
	pdPadBtn[3].btnData = CELL_PAD_CTRL_SQUARE;
	pdPadBtn[4].btnData = CELL_PAD_CTRL_TRIANGLE;
	pdPadBtn[5].btnData = CELL_PAD_CTRL_L1;
	pdPadBtn[6].btnData = CELL_PAD_CTRL_R1;
	pdPadBtn[7].btnData = CELL_PAD_CTRL_L3;
	pdPadBtn[8].btnData = CELL_PAD_CTRL_R3;
	pdPadBtn[9].btnData = CELL_PAD_CTRL_L2;
	pdPadBtn[10].btnData = CELL_PAD_CTRL_R2;
	pdPadBtn[11].btnData = CELL_PAD_CTRL_UP;
	pdPadBtn[12].btnData = CELL_PAD_CTRL_DOWN;
	pdPadBtn[13].btnData = CELL_PAD_CTRL_LEFT;
	pdPadBtn[14].btnData = CELL_PAD_CTRL_RIGHT;

	pdPadBtn[0].btnDigital = 0;
	pdPadBtn[1].btnDigital = 1;
	pdPadBtn[2].btnDigital = 1;
	pdPadBtn[3].btnDigital = 1;
	pdPadBtn[4].btnDigital = 1;
	pdPadBtn[5].btnDigital = 1;
	pdPadBtn[6].btnDigital = 1;
	pdPadBtn[7].btnDigital = 0;
	pdPadBtn[8].btnDigital = 0;
	pdPadBtn[9].btnDigital = 1;
	pdPadBtn[10].btnDigital = 1;
	pdPadBtn[11].btnDigital = 0;
	pdPadBtn[12].btnDigital = 0;
	pdPadBtn[13].btnDigital = 0;
	pdPadBtn[14].btnDigital = 0;
}
#endif