{
ID:os.idea1
PROG:sprime
LANG:PASCAL
}
const su:array[1..6] of integer=(1,2,3,5,7,9);
var n:longint;

function check(s:longint):boolean;
var i:longint;
begin
  if s=2 then exit(true);
  for i:=2 to trunc(sqrt(s))+1 do
    if s mod i=0 then exit(false);
  exit(true);
end;

procedure search(s,tn:longint);
var i,j,ts:longint;
begin
  if tn=n then begin
    writeln(s);
    exit;
  end;
  if tn=0 then j:=2 else j:=1;
  for i:=j to 6 do begin
    ts:=s*10+su[i];
    if check(ts) then search(ts,tn+1);
  end;
end;

begin
  assign(input,'sprime.in');assign(output,'sprime.out');
  reset(input);rewrite(output);
  readln(n);
  search(0,0);
  close(input);close(output);
end.
