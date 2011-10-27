{
ID:os.idea1
PROG:packrec
LANG:PASCAL
}
var
  n,i,j,s1,s2,s3,s4,d1,d2,d3,d4,w,h:byte;
  sq:array[1..4,1..2]of byte;
  mr:word;
  re:array[0..10,1..2]of byte;

function max (a,b,c,d:byte):byte;
begin
  if a>b then
    if a>c then
      if a>d then
        exit(a)
      else
        exit(d)
    else
      if c>d then
        exit(c)
      else
        exit(d)
  else
    if b>c then
      if b>d then
        exit(b)
      else
        exit(d)
    else
      if c>d then
        exit(c)
      else
        exit(d);
end;

procedure fresh;
var
  i,s:byte;
begin
  if w*h>mr then
    exit;
  if w*h<mr then
  begin
    mr:=w*h;
    n:=0;
  end;
  if w>h then
  begin
    s:=w;
    w:=h;
    h:=s;
  end;
  for i:=1 to n do
    if (re[i,1]=w) and (re[i,2]=h) then
      exit;
  inc(n);{开一个新档案}
  re[n,1]:=w;
  re[n,2]:=h;
end;

procedure calc;
var
  w1,w2,w3,w4,h1,h2,h3,h4:byte;
begin
  w1:=sq[s1,d1];
  w2:=sq[s2,d2];
  w3:=sq[s3,d3];
  w4:=sq[s4,d4];
  h1:=sq[s1,3-d1];
  h2:=sq[s2,3-d2];
  h3:=sq[s3,3-d3];
  h4:=sq[s4,3-d4];
  w:=w1+w2+w3+w4;
  h:=max(h1,h2,h3,h4);
  fresh; {图1}
  w:=max(w1+w2+w3,w4,0,0);
  h:=max(h1,h2,h3,0)+h4;
  fresh; {图2}
  w:=max(w1+w2,w3,0,0)+w4;
  h:=max(max(h1,h2,0,0)+h3,h4,0,0);
  fresh; {图3}
  w:=w1+w2+max(w3,w4,0,0);
  h:=max(h1,h2,h3+h4,0);
  fresh; {图4/5}
  h:=max(h1+h3,h2+h4,0,0);
  if h4>=h1+h3 then
    w:=max(w2,w1+w4,w3+w4,0);
  if h3>=h2+h4 then
    w:=max(w1,w2+w3,w4+w3,0);
  if (h3>h4) and (h3<h4+h2) then
    w:=max(w1+w2,w2+w3,w3+w4,0);
  if (h4>h3) and (h4<h3+h1) then
    w:=max(w1+w2,w1+w4,w3+w4,0);
  if (h3=h4) then
    w:=max(w3+w4,w1+w2,0,0);
  fresh; {图6}
end;

begin
  assign(input,'packrec.in');
  assign(output,'packrec.out');
  reset(input);
  rewrite(output);
  for i:=1 to 4 do
    readln(sq[i,1],sq[i,2]);
  n:=0;
  mr:=$FFFF;
  for s1:=1 to 4 do
    for s2:=1 to 4 do
      if (s2<>s1) then
        for s3:=1 to 4 do
          if (s3<>s2) and (s3<>s1) then
          begin
            s4:=10-s1-s2-s3; {将第1~4块矩形所有情况列举}
            for d1:=1 to 2 do
              for d2:=1 to 2 do
                for d3:=1 to 2 do
                  for d4:=1 to 2 do {确定1~4块矩形的横/竖排放方式}
                    calc;
          end;
  for i:=1 to n-1 do
    for j:=i+1 to n do
      if re[i,1]>re[j,1] then
      begin
        re[0]:=re[i];
        re[i]:=re[j];
        re[j]:=re[0];
      end;
  writeln(mr);
  for i:=1 to n do
    writeln(re[i,1],' ',re[i,2]);
  close(output);
end.