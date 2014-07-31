{
ID:os.idea1
PROG:milk3
LANG:PASCAL
}
var a,b,c,cp:longint;
    sc:array[1..20] of longint;
    check:array[0..20,0..20] of boolean;

procedure sort(l,r:longint);
var i,j,mid,temp:longint;
begin
  i:=l;j:=r;mid:=sc[(i+j) div 2];
  repeat
    while sc[i]<mid do inc(i);
    while sc[j]>mid do dec(j);
    if i<=j then begin
      temp:=sc[i];sc[i]:=sc[j];sc[j]:=temp;
      inc(i);dec(j);
    end;
  until i>j;
  if i<r then sort(i,r);
  if j>l then sort(l,j);
end;

procedure change(var i,j:longint;k:longint);
begin
  if i+j>k then begin
    i:=i-(k-j);
    j:=k;
  end
  else begin
    j:=j+i;
    i:=0;
  end;
end;

procedure dfs(ta,tb,tc:longint);
var tpa,tpb,tpc:longint;
begin
  if check[tb,tc] then exit;
  if ta=0 then begin
    inc(cp);
    sc[cp]:=tc;
  end;

  check[tb,tc]:=true;
  tpa:=ta;tpb:=tb;tpc:=tc;

  if ta<>0 then begin
    change(ta,tb,b);
    dfs(ta,tb,tc);

    ta:=tpa;tb:=tpb;tc:=tpc;
    change(ta,tc,c);
    dfs(ta,tb,tc);
  end;

  ta:=tpa;tb:=tpb;tc:=tpc;
  if tb<>0 then begin
    change(tb,ta,a);
    dfs(ta,tb,tc);

    ta:=tpa;tb:=tpb;tc:=tpc;
    change(tb,tc,c);
    dfs(ta,tb,tc);
  end;

  ta:=tpa;tb:=tpb;tc:=tpc;
  if tc<>0 then begin
    change(tc,ta,a);
    dfs(ta,tb,tc);

    ta:=tpa;tb:=tpb;tc:=tpc;
    change(tc,tb,b);
    dfs(ta,tb,tc);
  end;
end;

begin
  assign(input,'milk3.in');assign(output,'milk3.out');
  reset(input);rewrite(output);
  readln(a,b,c);
  cp:=0;
  fillchar(check,sizeof(check),0);
  dfs(0,0,c);
  sort(1,cp);
  for a:=1 to cp-1 do write(sc[a], ' ');
  writeln(sc[cp]);
  close(input);close(output);
end.
