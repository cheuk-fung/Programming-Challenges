/*
 *  SRC: HDOJ 4269
 * PROB: Defend Jian Ge
 * ALGO: Implementation
 * DATE: Sep 08, 2012
 * COMP: jdk6
 *
 * Created by Leewings Ng
 */

import java.io.*;
import java.util.*;

class Main {
    class Item implements Comparable {
        String name;
        int val;
        int cnt;

        Item(String[] str)
        {
            this.name = str[0];
            this.val = Integer.parseInt(str[1]);
            this.cnt = 1;
        }

        Item(String name, int val, int cnt)
        {
            this.name = name;
            this.val = val;
            this.cnt = cnt;
        }

        public int compareTo(Object other)
        {
            return name.compareTo(((Item)other).name);
        }

        public String toString()
        {
            return name + ": " + cnt;
        }
    }

    void run() throws IOException
    {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);

        int tasks = 1;
        while (true) {
            String line = br.readLine();
            if (line == null) break;

            int n1 = Integer.parseInt(line);
            Item[] noreq = new Item[n1];
            for (int i = 0; i < n1; i++) {
                line = br.readLine();
                noreq[i] = new Item(line.split(" "));
            }

            // cut here
            // for (int i = 0; i < n1; i++) {
            //    System.out.println(noreq[i]);
            // }
            // cut end

            int n2 = Integer.parseInt(br.readLine());
            Item[] mixeq = new Item[n2];
            ArrayList<Item> mixrec[] = new ArrayList[n2];
            for (int i = 0; i < n2; i++) {
                line = br.readLine();
                String[] now = line.split(": ");
                mixeq[i] = new Item(now[0].split(" "));
                mixrec[i] = new ArrayList<Item>();
                if (now.length == 1) continue;
                for (String seg : now[1].split(", ")) {
                    mixrec[i].add(new Item(seg.split(" ")));
                }
            }
            // cut here
            // for (int i = 0; i < n2; i++) {
            //     System.out.print(mixeq[i] + ": ");
            //     for (Item now : mixrec[i]) {
            //         System.out.print(" " + now);
            //     }
            //     System.out.println();
            // }
            // cut end

            int n3 = Integer.parseInt(br.readLine());
            Item[] coneq = new Item[n3];
            for (int i = 0; i < n3; i++) {
                line = br.readLine();
                coneq[i] = new Item(line.split(" "));
            }
            // cut here
            // for (int i = 0; i < n3; i++) {
            //     System.out.println(coneq[i]);
            // }
            // cut end

            int m = Integer.parseInt(br.readLine());
            int gold = 0;
            ArrayList<Item> pack = new ArrayList<Item>();
            while (m-- > 0) {
                line = br.readLine();
                if (line.charAt(0) == '+') {
                    // System.out.println("-" + line.substring(1));

                    if ('0' <= line.charAt(1) && line.charAt(1) <= '9') {
                        gold += Integer.parseInt(line.substring(1));
                        continue;
                    }

                    String name = line.substring(1);
                    boolean ok = false;
                    for (Item now : noreq) {
                        if (now.name.equals(name)) {
                            ok = true;
                            if (gold >= now.val && pack.size() < 6) {
                                gold -= now.val;
                                pack.add(new Item(now.name, now.val, 1));
                                break;
                            }
                        }
                    }
                    if (ok) continue;

                    for (Item now : coneq) {
                        if (now.name.equals(name)) {
                            ok = true;
                            if (gold >= now.val && pack.size() < 6) {
                                gold -= now.val;

                                boolean well = false;
                                for (Item inpack : pack) {
                                    if (inpack.name.equals(name)) {
                                        inpack.cnt++;
                                        well = true;
                                        break;
                                    }
                                }
                                if (!well) {
                                    pack.add(new Item(now.name, now.val, 1));
                                }
                            }
                            break;
                        }
                    }
                    if (ok) continue;

                    for (int i = 0; i < mixeq.length; i++) {
                        Item now = mixeq[i];
                        if (now.name.equals(name)) {
                            if (gold >= now.val) {
                                boolean well = true;
                                boolean release = false;
                                for (Item part : mixrec[i]) {
                                    int cnt = part.val;
                                    for (Item inpack : pack) {
                                        if (inpack.name.equals(part.name)) {
                                            if (inpack.cnt <= cnt) release = true;
                                            cnt -= inpack.cnt;
                                        }
                                    }
                                    if (cnt > 0) {
                                        well = false;
                                        break;
                                    }
                                }
                                if (!well) break;
                                if (!release && pack.size() >= 6) break;

                                gold -= now.val;
                                int val = now.val;
                                for (Item part : mixrec[i]) {
                                    int cnt = part.val;
                                    for (Item inpack : pack) {
                                        if (inpack.name.equals(part.name)) {
                                            if (cnt <= inpack.cnt) {
                                                inpack.cnt -= cnt;
                                                val += inpack.val * cnt;
                                                break;
                                            } else {
                                                cnt -= inpack.cnt;
                                                val += inpack.val * inpack.cnt;
                                                inpack.cnt = 0;
                                            }
                                        }
                                    }
                                }

                                ok = false;
                                while (!ok) {
                                    ok = true;
                                    for (int j = 0; j < pack.size(); j++) {
                                        if (pack.get(j).cnt == 0) {
                                            pack.remove(j);
                                            ok = false;
                                            break;
                                        }
                                    }
                                }
                                pack.add(new Item(name, val, 1));
                            }
                            break;
                        }
                    }
                } else {
                    // System.out.println("-" + line.substring(1));

                    String name = line.substring(1);
                    for (int i = 0; i < pack.size(); i++) {
                        if (pack.get(i).name.equals(name)) {
                            gold += pack.get(i).val * pack.get(i).cnt;
                            pack.remove(i);
                            break;
                        }
                    }
                }
            }

            /*System.*/out.println("Case " + tasks++ + ":");
            /*System.*/out.println(gold);
            /*System.*/out.println(pack.size());
            Collections.sort(pack);
            for (Item inpack : pack) {
                /*System.*/out.println(inpack);
            }
            /*System.*/out.println();

            line = br.readLine();
        }

        out.flush();
    }

    public static void main(String[] args) throws IOException
    {
        new Main().run();
    }
}
