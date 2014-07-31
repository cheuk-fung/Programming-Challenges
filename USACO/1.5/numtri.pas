{
ID:os.idea1
PROG:numtri
LANG:PASCAL
}
var f:array[0..1000,0..1000] of longint;
    r,i,j:longint;

function max(a,b:longint):longint;
begin
  if a>b then exit(a) else exit(b);
end;


begin
  assign(input,'numtri.in');assign(output,'numtri.out');
  reset(input);rewrite(output);
  readln(r);
  for i:=1 to r do begin
    for j:=1 to i do read(f[i,j]);
    readln;
  end;
  for i:=r-1 downto 1 do
    for j:=1 to i do f[i,j]:=f[i,j]+max(f[i+1,j],f[i+1,j+1]);
  writeln(f[1,1]);
  close(input);close(output);
end.
