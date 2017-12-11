// Commands for Alpha Sign Communication Protocol
// it will accept plain ascii characters instead of control characters, just add 0x20 to the control code
/******************************
        Common Codes

    ]!  =   <SOH>
    ]"  =   <STX< (also ]\" )
    ]#  =   <ETX>
    ]$  =   <EOH>
    ];  =   <ESC>
    ]-  =   <CR>

    Z00 =   address all signs
    q00 =   address ppd?

    E   =   configure memory
    I   =   store custom DOTS image:  FYYXX DATA, F DOTS file label, YY y dimension, XX x dimension, data in x size chucks with <CR> between
    A   =   write TEXT file
    G   =   update STRING


******************************/


void setup()
{
    Serial.begin(9600);

    clear_memory();
    config_memory();
    send_bitcoin_char();
    write_text_file();

    delay(500);
    frameSync();
    Serial.write("]!Z00]\"GP15850]#]\"GDDec 9 3:05 AM]$"); //update the strings


    delay(1000);
}

void loop()
{
    frameSync();
    Serial.write("]!Z00]\"GD");
    Serial.print(millis());
    Serial.write("]$");
    delay(100);
}

void frameSync(){
    delay(10); //delay between commands
    Serial.write(0x0); // Start frame sync chars
    Serial.write(0x0);
    Serial.write(0x0);
    Serial.write(0x0);
    Serial.write(0x0);
    Serial.write(0x0);
    Serial.write(0x0);
    Serial.write(0x0);
    Serial.write(0x0); // end frame sync chars
}

void clear_memory(){
    frameSync();
    Serial.write("]!Z00]\"E$]$"); //clear memory E$
    delay(2000); //unit takes a while to become responsive again
}

void config_memory(){
    frameSync();
    Serial.write("]!Z00]\"E$AAU000AFE00!AL04D0FF00!DL07054000PBL002D0000DBL002D0000]#]\"E2!A1]$");
    /*  command breakdown:
        E$              =   configure memory
        AAU000AFE00     =   A file label, A = TEXT, unlocked (can be edited by IR remote), size = 0xA, mode = 0xFE00 for never display (can't have DOTS images in TEXT file A either! this isn't used)
        !AL04D0FF00     =   ! file test, A = TEXT, locked, size 0x04D0, mode 0xFF00 always display
        !DL07054000     =   ! file label, D = DOTS, locked (must be?), size 07 height 05 width, mode 4000 RGB (dunno why, but it works)
        PBL002D0000     =   P file label, B = STRING, locked (must be!), size 0x2D, mode 0000 strings don't use mode
        DBL002D0000     =   D file label, B = STRING, locked (must be!), size 0x2D, mode 0000 strings don't use mode

        E2!A1           =   set TEXT file ! to always display
    */
    delay(100);
}

void send_bitcoin_char(){
    frameSync();
    Serial.write("]!Z00]\"I!070501010]-11110]-10001]-11110]-10001]-11110]-01010]-]$"); //send bitcoin symbol
    /*
        .1.1.
        1111.
        1...1
        1111.
        1...1
        1111.
        .1.1.
    */
}

void write_text_file(){
    frameSync();
    Serial.write("]!Z00]\"A!];0b])]4!1 = $]0P]-]0D   ]$");
    // A write TEXT file, ! file label, ];0b]) is <ESC> fill, hold, no hold speed (quick update for strings), ]4! display DOTS image !, 1 = $ actual message, ]0P display STRING P
    // ]- <CR>, ]0D display STRING D
}


