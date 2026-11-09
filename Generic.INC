
{Unit generic.inc – contains general‑purpose procedures}
{to be included after Msx.inc in Turbo Pascal programs for MSX}


Const

  KR_F1 = 6; KB_F1 = 5;
  KR_F2 = 6; KB_F2 = 6;
  KR_F3 = 6; KB_F3 = 7;
  KR_F4 = 7; KB_F4 = 0;
  KR_F5 = 7; KB_F5 = 1;

Var
  Keys    : Array[0..10] Of Byte;
  OldKeys : Array[0..10] Of Byte;

{Converts an integer number into a 4‑character hexadecimal string}
FUNCTION Hex(n: INTEGER): str4;
CONST
  HexDig: ARRAY[0..15] OF CHAR ='0123456789ABCDEF';
VAR
  s: str4;
BEGIN
  s := '';
  s := s + HexDig[(n SHR 12) AND $0F];
  s := s + HexDig[(n SHR  8) AND $0F];
  s := s + HexDig[(n SHR  4) AND $0F];
  s := s + HexDig[(n       ) AND $0F];
  Hex := s;
END;


{executes the BASIC command contained in the string macro}
Procedure  basic(macro : STR255 );
Var calbas : string[9] absolute $F6EF;
    retbas : string[5] absolute $FF3D;
    arg  : STR255  absolute $F55F ;
BEGIN
  calbas := #$DB + #$A8 + #$F5 + #$E6 + #$F0 + #$C3 + #$8C + #$F3;
  retbas := #$7E + #$A7 + #$C0 + #$F1;
  arg := macro + #0 ;
  inline
  ($21/$5F/$F5/    { LD HL,F55FH }
   $DD/$21/$73/$41/{ LD IX,4173H }
   $CD/$F0/$F6 );  { CALL F6F0H  }
END;

{Plays a beep}
procedure beep;
begin
   
   MsxBios(BEP);

END;

{compute base^esponente}
function Power(base, esponente: real): real;
begin
  Power := exp(esponente * ln(base));
end;

{read the rom adresses when page is mapped differently - e.g. under MsxDos}
function PeekBIOS(addr:integer):byte;
begin
RegHL:=addr;

inline(
$3A/$C1/$FC/ { LD A,(EXPTBL) }
$2A/RegHL/ { LD HL,(RegHL) }
$CD/$0C/$00/ { CALL RDSLT }
$32/RegA { LD (RegA),A }
);

PeekBIOS:=RegA;
end;

{Read a memory location}
function Peek(addr: integer): byte;
var
  b: byte;
begin

  RegHL:=addr;
  inline(
    $2A/RegHL/   { LD HL,hi*256+lo }
    $7E/         { LD A,(HL) }
    $32/RegA     { LD RegA,A }
  );

  Peek := RegA;

end;

{Write in a memory location}
procedure Poke(addr: integer; value: byte);
begin
RegHL:=addr;
RegA:=value;

inline(
$2A/RegHL/ { LD HL,(RegHL) }
$3A/RegA/ { LD A,(RegA) }
$77 { LD (HL),A }
);

mem[addr] := value; 
end;

{Convert an integer into a string}
function Str(n: integer): str6;
var
  s: string[6];
  m: integer;
begin
  s := '';
  m := n;

  if m < 0 then
  begin
    s := '-';
    m := -m;
  end;

  repeat
    s := chr(ord('0') + (m mod 10)) + s;
    m := m div 10;
  until m = 0;

  Str := s;
end;


{these procedure and function, KeyScan, Keydows, Keypresse, are propedeutic to the function FunctionKeyPressed}
{Returns true if the key in the keyboard matrix bit is down (pressed)}
Function KeyDown(Row,Bit:Byte):Boolean;
Begin
  KeyDown := (Keys[Row] And (1 Shl Bit))=0;
End;

{Returns true if the key in the keyboard matrix bit is pressed (down) and was not pressed in the previous scan}
Function KeyPresse(Row,Bit:Byte):Boolean;
Begin
  KeyPresse :=
    ((OldKeys[Row] And (1 Shl Bit))<>0) and
    ((Keys[Row] And (1 Shl Bit))=0);
End;


{Scan the keyboard matrix and return the result in a byte}
{Each bit of the returned byte represents a keyboard button, 0=pressed, 1=not pressed}
{Illegal row numbers (above 15) will be masked off.}
Function KeyScan(Row:Byte):Byte;
var
value:byte;
 Begin
 RegA:=Row;

     Inline( $f3/$db/$aa/ $e6/ $f0/$47
            /$3a/ RegA /$e6/$0f/ $b0/ $d3/$aa/
             $db/$a9/$32/Value /
             $fb
           );
     KeyScan := Value;
 End;


{end of propedeutic functions and procedures for FunctionKeyPressed }


{Init the keyboard buffer}
Procedure InitKeyboard;
Var
  i : Byte;
Begin
  For i:=0 To 10 Do
  Begin
    Keys[i]:=keyscan(i);
    OldKeys[i] := Keys[i];
  End;
End;

{Update the keyboard buffer}
Procedure UpdateKeyboard;
Var
  i : Byte;
Begin
  For i:=0 To 10 Do
  Begin
    OldKeys[i] := Keys[i];
    Keys[i] := KeyScan(i);
  End;
End;


{Return the Function key pressed 1 to 10}
Function FunctionKeyPressed:Byte;
Var Shift : Boolean;
BEGIN
  Shift:=Keydown(6,0);

  FunctionKeyPressed:=0;

  If KeyPresse(6,5) Then
    If Shift Then FunctionKeyPressed:=6
             Else FunctionKeyPressed:=1

  Else If KeyPresse(6,6) Then
    If Shift Then FunctionKeyPressed:=7
             Else FunctionKeyPressed:=2

  Else If KeyPresse(6,7) Then
    If Shift Then FunctionKeyPressed:=8
             Else FunctionKeyPressed:=3

  Else If KeyPresse(7,0) Then
    If Shift Then FunctionKeyPressed:=9
             Else FunctionKeyPressed:=4

  Else If KeyPresse(7,1) Then
    If Shift Then FunctionKeyPressed:=10
             Else FunctionKeyPressed:=5;
END;


{Delete the content of the function key buffer}
procedure DelFKey;
Var i: integer;

BEGIN

for i:=0 to 160 do
Poke (FNKSTR+i,0);
END;

{Set the content of a keuynum function key}
Procedure SetFKey(keynum:byte;content:str16);
Var i,c,j,l: byte;

BEGIN
l:=length(content);
if (l>15) then l:=15;
i:=(keynum-1)*16;
for j:=1 to l do
begin
c:=ord(copy(content,j,1));

Poke (FNKSTR+(keynum-1)+j-1,c);
end;
END;


{internal synchronization routine to call the internal command of Vdp}
Procedure Common;

BEGIN 
	Inline  (
          $F3/$3E/$20/$D3/$99/$3E/$91/$D3/$99/$0E/$9B/$21/$62/$F5/$ED/$A3/$ED/
          $A3/$ED/$A3/$ED/$A3/$ED/$A3/$ED/$A3/$ED/$A3/$ED/$A3/$ED/$A3/$ED/$A3/
          $ED/$A3/$ED/$A3/$ED/$A3/$ED/$A3/$ED/$A3/$3E/$02/$D3/$99/$3E/$80/$F6/$0f/
          $D3/$99/$DB/$99/$CB/$47/$20/$F0/$AF/$D3/$99/$3E/$8F/$D3/$99/$FB
          );
END;

{the same as INKEY$ Function in BASIC, returns the first character in the keyboard buffer, or #0 if the buffer is empty}
function Inkey(key:char):char;
BEGIN
REPEAT
READ(KBD,key);
UNTIL key<>#0;
inkey:=key;
END;