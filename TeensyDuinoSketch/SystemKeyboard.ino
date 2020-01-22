// ----------------------------------------------------------------------------------
// -- Company: 
// -- Engineer: anightin
// -- 
// -- Create Date:    20:00:00 01/01/2020 
// -- Design Name: 
// -- Module Name:    SystemKeyboard.ino
// -- Project Name: 
// -- Target Devices: Acorn SYSTEM 2/3/5, HID USB Keyboard
// -- Tool versions: 
// -- Description: 
// --
// -- Dependencies: 
// --
// -- Revision: 
// -- Revision 0.02 - Tidy up code and correct pin assignments -- functionally equivalent
// -- Additional Comments: 
// --
// ----------------------------------------------------------------------------------
//
// Keyboard micro-manager command reference :-
//
// 1) Set key modifiers then send them as being pressed
//
// Keyboard.set_modifier(0);
// or 
// Keyboard.set_modifier(MODIFIERKEY_CTRL | MODIFIERKEY_RIGHT_CTRL |
//   MODIFIERKEY_SHIFT | MODIFIERKEY_RIGHT_SHIFT |
//   MODIFIERKEY_ALT | MODIFIERKEY_RIGHT_ALT |
//   MODIFIERKEY_GUI | MODIFIERKEY_RIGHT_GUI);
// Keyboard.send_now();
//
// 2) Up to 6 keys can be selected at once for pressing
//
// Keyboard.set_key1(KEY_A);
// Keyboard.set_key2(KEY_B);
// Keyboard.set_key3(KEY_C);
// Keyboard.set_key4(KEY_D);
// Keyboard.set_key5(KEY_E);
// Keyboard.set_key6(KEY_F); 
//
// 3) Send the key(s) as being pressed
//
// Keyboard.send_now();
//
// 4) Then release all modifier keys and normal keys at once
//
// Keyboard.set_modifier(0);
// Keyboard.set_key1(0);
// Keyboard.set_key2(0);
// Keyboard.set_key3(0);
// Keyboard.set_key4(0);
// Keyboard.set_key5(0);
// Keyboard.set_key6(0);
// Keyboard.send_now();

// Key lookup globals -- based on USB English UK Mapping
const byte KBNORM = 0x00;
const byte KBSHFT = 0x01;
const byte KBCTRL = 0x02;
const byte KBCTSH = 0x04;
const unsigned short matrix[][3] = {
  
  {0x09,  KEY_TAB,      KBNORM},          // TAB
  {0x0A,  KEY_DOWN,     KBNORM},          // LINEFEED == DOWN ARROW
  {0x0D,  KEY_ENTER,    KBNORM},          // RETURN
  {0x1B,  KEY_LEFT,     KBNORM},          // ESC == LEFT ARROW
  {0x20,  KEY_SPACE,    KBNORM},          // SPACE BAR
  {0x7F,  KEY_BACKSPACE,KBNORM},          // DELETE

  {0x30,  KEY_0,  KBNORM},          // 0
  {0x31,  KEY_1,  KBNORM},          // 1
  {0x32,  KEY_2,  KBNORM},          // 2
  {0x33,  KEY_3,  KBNORM},          // 3
  {0x34,  KEY_4,  KBNORM},          // 4
  {0x35,  KEY_5,  KBNORM},          // 5
  {0x36,  KEY_6,  KBNORM},          // 6
  {0x37,  KEY_7,  KBNORM},          // 7
  {0x38,  KEY_8,  KBNORM},          // 8
  {0x39,  KEY_9,  KBNORM},          // 9
  
  {0x21,  KEY_1,  KBSHFT},          // !
  {0x22,  KEY_QUOTE,  KBSHFT},      // "
  {0x23,  KEY_3,  KBSHFT},          // #
  {0x24,  KEY_4,  KBSHFT},          // $
  {0x25,  KEY_5,  KBSHFT},          // %
  {0x26,  KEY_7,  KBSHFT},          // &
  {0x27,  KEY_QUOTE,  KBNORM},      // '
  {0x28,  KEY_9,  KBSHFT},          // (
  {0x29,  KEY_0,  KBSHFT},          // )

  {0x61,  KEY_A,   KBNORM},         // a
  {0x62,  KEY_B,   KBNORM},         // b
  {0x63,  KEY_C,   KBNORM},         // c
  {0x64,  KEY_D,   KBNORM},         // d
  {0x65,  KEY_E,   KBNORM},         // e
  {0x66,  KEY_F,   KBNORM},         // f
  {0x67,  KEY_G,   KBNORM},         // g
  {0x68,  KEY_H,   KBNORM},         // h
  {0x69,  KEY_I,   KBNORM},         // i
  {0x6A,  KEY_J,   KBNORM},         // j
  {0x6B,  KEY_K,   KBNORM},         // k
  {0x6C,  KEY_L,   KBNORM},         // l
  {0x6D,  KEY_M,   KBNORM},         // m
  {0x6E,  KEY_N,   KBNORM},         // n
  {0x6F,  KEY_O,   KBNORM},         // o
  {0x70,  KEY_P,   KBNORM},         // p
  {0x71,  KEY_Q,   KBNORM},         // q
  {0x72,  KEY_R,   KBNORM},         // r
  {0x73,  KEY_S,   KBNORM},         // s
  {0x74,  KEY_T,   KBNORM},         // t
  {0x75,  KEY_U,   KBNORM},         // u
  {0x76,  KEY_V,   KBNORM},         // v
  {0x77,  KEY_W,   KBNORM},         // w
  {0x78,  KEY_X,   KBNORM},         // x
  {0x79,  KEY_Y,   KBNORM},         // y
  {0x7A,  KEY_Z,   KBNORM},         // z

  {0x41,  KEY_A,  KBSHFT},          // A
  {0x42,  KEY_B,  KBSHFT},          // B
  {0x43,  KEY_C,  KBSHFT},          // C
  {0x44,  KEY_D,  KBSHFT},          // D
  {0x45,  KEY_E,  KBSHFT},          // E
  {0x46,  KEY_F,  KBSHFT},          // F
  {0x47,  KEY_G,  KBSHFT},          // G
  {0x48,  KEY_H,  KBSHFT},          // H
  {0x49,  KEY_I,  KBSHFT},          // I
  {0x4A,  KEY_J,  KBSHFT},          // J
  {0x4B,  KEY_K,  KBSHFT},          // K
  {0x4C,  KEY_L,  KBSHFT},          // K
  {0x4D,  KEY_M,  KBSHFT},          // M
  {0x4E,  KEY_N,  KBSHFT},          // N
  {0x4F,  KEY_O,  KBSHFT},          // O
  {0x50,  KEY_P,  KBSHFT},          // P
  {0x51,  KEY_Q,  KBSHFT},          // Q
  {0x52,  KEY_R,  KBSHFT},          // R
  {0x53,  KEY_S,  KBSHFT},          // S
  {0x54,  KEY_T,  KBSHFT},          // T
  {0x55,  KEY_U,  KBSHFT},          // U
  {0x56,  KEY_V,  KBSHFT},          // V
  {0x57,  KEY_W,  KBSHFT},          // W
  {0x58,  KEY_X,  KBSHFT},          // X
  {0x59,  KEY_Y,  KBSHFT},          // Y
  {0x5A,  KEY_Z,  KBSHFT},          // Z
  {0x3A,  KEY_SEMICOLON,    KBSHFT},// :
  {0x3C,  KEY_COMMA,        KBSHFT},// <
  {0x3E,  KEY_PERIOD,       KBSHFT},// >
  {0x3F,  KEY_SLASH,        KBSHFT},// ?
  {0x7B,  KEY_LEFT_BRACE,   KBSHFT},// {
  {0x7D,  KEY_RIGHT_BRACE,  KBSHFT},// }
 
  {0x2C,  KEY_COMMA,        KBNORM},// ,
  {0x2D,  KEY_MINUS,        KBNORM},// -
  {0x2E,  KEY_PERIOD,       KBNORM},// .
  {0x2F,  KEY_SLASH,        KBNORM},// /
  {0x3B,  KEY_SEMICOLON,    KBNORM},// ;
  {0x40,  KEY_2,            KBSHFT},// @
  {0x5B,  KEY_LEFT_BRACE,   KBNORM},// [
  {0x5C,  KEY_BACKSLASH,    KBNORM},// '\'
  {0x5D,  KEY_RIGHT_BRACE,  KBNORM},// ]
  {0x5E,  KEY_6,            KBSHFT},// ^
  {0x5F,  KEY_MINUS,        KBNORM},// _
  {0x2A,  KEY_8,            KBSHFT},// *
  {0x2B,  KEY_EQUAL,        KBSHFT},// +
  {0x7C,  KEY_BACKSLASH,    KBSHFT},// |
  {0x7E,  KEY_TILDE,        KBSHFT},// ~
  {0x3D,  KEY_EQUAL,        KBNORM},// =

  {0x01,  KEY_A,  KBCTRL},          // SOH
  {0x02,  KEY_B,  KBCTRL},          // STX
  {0x03,  KEY_C,  KBCTRL},          // ETX
  {0x04,  KEY_D,  KBCTRL},          // EOT
  {0x05,  KEY_E,  KBCTRL},          // ENQ
  {0x06,  KEY_F,  KBCTRL},          // ACK
  {0x07,  KEY_G,  KBCTRL},          // BELL
  {0x08,  KEY_H,  KBCTRL},          // BS
  {0x0B,  KEY_I,  KBCTRL},          // VT
  {0x0C,  KEY_J,  KBCTRL},          // FF
  {0x0E,  KEY_K,  KBCTRL},          // S0
  {0x0F,  KEY_L,  KBCTRL},          // S1
  {0x10,  KEY_M,  KBCTRL},          // DLE
  {0x11,  KEY_N,  KBCTRL},          // DC1
  {0x12,  KEY_O,  KBCTRL},          // DC2
  {0x13,  KEY_P,  KBCTRL},          // DC3
  {0x14,  KEY_Q,  KBCTRL},          // DC4
  {0x15,  KEY_R,  KBCTRL},          // NAK
  {0x16,  KEY_S,  KBCTRL},          // SYN
  {0x17,  KEY_T,  KBCTRL},          // ETB
  {0x18,  KEY_U,  KBCTRL},          // CAN
  {0x19,  KEY_V,  KBCTRL},          // EM
  {0x1A,  KEY_W,  KBCTRL},          // SUB
  {0x1F,  KEY_MINUS,        KBCTRL},// US
  {0x1C,  KEY_SEMICOLON,    KBCTRL},// FS 
  {0x1D,  KEY_RIGHT_BRACE,  KBCTRL},// GS
  {0x1E,  KEY_TILDE,        KBCTRL},// RS
  {0x00,  0X00,             KBCTRL},// NUL

  {0xFF,  0xFF,   KBNORM|KBCTSH}    // Undefined!
  };

// Globals
const byte DATA0 = PIN_B0; 
const byte DATA1 = PIN_B1; 
const byte DATA2 = PIN_B2; 
const byte DATA3 = PIN_B3; 
const byte DATA4 = PIN_B4; 
const byte DATA5 = PIN_B5; 
const byte DATA6 = PIN_B6; 
const unsigned short keyCodeBLANK = KEY_RIGHT; // RIGHT ARROW
const unsigned short keyCodeNRST = KEY_UP; // UP ARROW
const unsigned short keyDEFAULT = 0x0000;
const byte ledPin = PIN_D6;
const byte interruptPin0 = PIN_D0;
const byte interruptPin1 = PIN_D1;
const byte interruptPin2 = PIN_D2;
volatile byte BLANKstate = LOW;
volatile byte NSTROBEstate = LOW;
volatile byte NRSTstate = LOW;
byte oldBLANKstate = LOW;
byte oldNSTROBEstate = LOW;
byte oldNRSTstate = LOW;
bool newBLANK = false;
bool newNSTROBE = false;
bool newNRST = false;
bool newState = false;
byte keyASCII = 0x00;
unsigned short keyCode = keyDEFAULT;
bool rawMode = false;

// Setup inputs and ISRs
void setup() { 
  // Configure parallel ASCII keyboard output and signals
  pinMode(DATA0, INPUT_PULLUP);
  pinMode(DATA1, INPUT_PULLUP);
  pinMode(DATA2, INPUT_PULLUP);
  pinMode(DATA3, INPUT_PULLUP);
  pinMode(DATA4, INPUT_PULLUP);
  pinMode(DATA5, INPUT_PULLUP);
  pinMode(DATA6, INPUT_PULLUP);

  // LED status and Interrupt Pin Setup
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin0, INPUT_PULLUP);
  pinMode(interruptPin1, INPUT_PULLUP);
  pinMode(interruptPin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin0), BLANK,    FALLING);
  attachInterrupt(digitalPinToInterrupt(interruptPin1), NRST,     FALLING);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), NSTROBE,  FALLING);
}// setup

// Repeat loop to check if there is any activity
void loop() {
  // Check to see if any of the status bits have changed
  if (oldBLANKstate != BLANKstate) {
    newState = newBLANK = true;
    oldBLANKstate = BLANKstate;
  }
  if (oldNRSTstate != NRSTstate) {
    newState = newNRST = true;
    oldNRSTstate = NRSTstate;
  }
  if (oldNSTROBEstate != NSTROBEstate) {
    newState = newNSTROBE = true;
    oldNSTROBEstate = NSTROBEstate;
  }
  // Determine what to do if a new state change
  if (newState) { 
    byte keyModifier = KBNORM;
    newState = false;
    if (newBLANK) {
      // Assign KeyCode for BLANK
      keyCode = keyCodeBLANK;   
    }    
    if (newNRST) {
      // Assign KeyCode for NRST
      keyCode = keyCodeNRST;
    }    
    if (newNSTROBE) {
      // Read Key code bits
      bitWrite(keyASCII, 0, digitalRead(DATA0));
      bitWrite(keyASCII, 1, digitalRead(DATA1));
      bitWrite(keyASCII, 2, digitalRead(DATA2));
      bitWrite(keyASCII, 3, digitalRead(DATA3));
      bitWrite(keyASCII, 4, digitalRead(DATA4));
      bitWrite(keyASCII, 5, digitalRead(DATA5));
      bitWrite(keyASCII, 6, digitalRead(DATA6));
      bitWrite(keyASCII, 7, 0);
      keyCode = keyASCII;
      
      // See if we need to preserve raw key-press
      if (!rawMode) {
        keyModifier = translateKey(&keyCode);
      }
    } 
    // Pass on key
    if (keyModifier == KBCTRL) {
      // Ctrl then key
      Keyboard.set_modifier(MODIFIERKEY_CTRL);
      Keyboard.send_now();
      Keyboard.set_key1(keyCode);
      Keyboard.send_now();
      // Release
      Keyboard.set_modifier(0);
      Keyboard.set_key1(0);
      Keyboard.send_now();
    } else if (keyModifier == KBSHFT) {
      // Shift then key
      Keyboard.set_modifier(MODIFIERKEY_SHIFT);
      Keyboard.send_now();
      Keyboard.set_key1(keyCode);
      Keyboard.send_now();
      // Release
      Keyboard.set_modifier(0);
      Keyboard.set_key1(0);
      Keyboard.send_now();
    } else { // Send key straight through
      Keyboard.press(keyCode);
      Keyboard.release(keyCode);
    }
    
    // Clear state flags
    newBLANK = newNRST = newNSTROBE= false;
    
    // Flash the LED to show that we've caught a new state
    digitalWrite(ledPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
    delay(50);
  }
}// loop

// ISRs
void BLANK() {
  BLANKstate = !BLANKstate;
}
void NSTROBE() {
  NSTROBEstate = !NSTROBEstate;
}
void NRST() {
  NRSTstate = !NRSTstate;
}

// Scan key lookup for key input, if found check if it needs a SHIFT or CTRL modifier
byte translateKey(unsigned short *rawKey) {
  byte result = KBNORM;
  int i=0;
  do {
    if (matrix[i][0] == *rawKey) {
      *rawKey = (unsigned short)matrix[i][1];
      result  = matrix[i][2];
      return result;
    }
  } while (matrix[i++][0] != 0xFF); 

  // If we get here we haven't recognised the key
  *rawKey = keyDEFAULT;
  return result;
}
// EOF
