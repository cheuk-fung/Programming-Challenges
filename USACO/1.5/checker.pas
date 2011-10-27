{
ID:os.idea1
PROG:checker
LANG:PASCAL
}
Uses sysutils;
var a,b,x,y:array[-13..13] of byte;
    n,ans,bn:longint;

procedure research1(tn:integer);
var i,j:integer;
begin
  if tn>n then begin
    inc(ans);
    exit;
  end;

  if a[tn]<>0 then begin
    research1(tn+1);
    exit;
  end;

  for i:=1 to n do
    if (b[i]=0) and (x[tn-i]=0) and (y[n-tn+1-i]=0) then begin
      a[tn]:=i;b[i]:=1;
      x[tn-i]:=1;y[n-tn+1-i]:=1;
      research1(tn+1);
      a[tn]:=0;b[i]:=0;
      x[tn-i]:=0;y[n-tn+1-i]:=0;
    end;

end;

procedure research2(tn:integer);
var i,j:integer;
begin
  if tn>n then begin
    inc(ans);
    exit;
  end;

  if tn=1 then j:=bn else j:=n;
  for i:=1 to j do
    if (b[i]=0) and (x[tn-i]=0) and (y[n-tn+1-i]=0) then begin
      a[tn]:=i;b[i]:=1;
      x[tn-i]:=1;y[n-tn+1-i]:=1;
      research2(tn+1);
      a[tn]:=0;b[i]:=0;
      x[tn-i]:=0;y[n-tn+1-i]:=0;
    end;
end;

procedure search(tn:integer);
var i,j:integer;
begin
  if tn>n then begin
    inc(ans);
    if ans<4 then begin
      for i:=1 to n-1 do write(a[i],' ');
      writeln(a[n]);
    end;
    if ans=3 then begin
      ans:=0;
      fillchar(a,sizeof(a),0);
      b:=a;x:=a;y:=a;
      if odd(n) then begin
        bn:=n div 2+1;
        for i:=1 to bn-1 do begin
          a[i]:=bn;b[bn]:=1;
          x[i-bn]:=1;y[n-i+1-bn]:=1;
          for j:=i+1 to bn-1 do begin
            a[bn]:=j;b[j]:=1;
            x[bn-j]:=1;y[n-bn+1-j]:=1;
            research1(1);
            a[bn]:=0;b[j]:=0;
            x[bn-j]:=0;y[n-bn+1-j]:=0;
          end;
          a[i]:=0;b[bn]:=0;
          x[i-bn]:=0;y[n-i+1-bn]:=0;
        end;
        ans:=ans*8;
        a[bn]:=bn;b[bn]:=1;
        x[0]:=1;y[0]:=1;
        research1(1);
      end
      else begin
        bn:=n div 2;
        research2(1);
        ans:=ans*2;
      end;
      writeln(ans);
      close(input);close(output);
      halt;
    end;
    exit;
  end;

  for i:=1 to n do
    if (b[i]=0) and (x[tn-i]=0) and (y[n-tn+1-i]=0) then begin
      a[tn]:=i;b[i]:=1;
      x[tn-i]:=1;y[n-tn+1-i]:=1;
      search(tn+1);
      a[tn]:=0;b[i]:=0;
      x[tn-i]:=0;y[n-tn+1-i]:=0;
    end;
end;

begin
  assign(input,'checker.in');assign(output,'checker.out');
  reset(input);rewrite(output);
  readln(n);
  fillchar(a,sizeof(a),0);
  b:=a;x:=a;y:=a;
  ans:=0;
  search(1);
  close(input);close(output);
end.
