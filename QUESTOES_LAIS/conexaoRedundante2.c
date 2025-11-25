public class Solution {
    public int[] FindRedundantDirectedConnection(int[][] edges) {

        for(int i = 0; i < 1001; i++){
            par[i] = -1;
            // chi[i] = false;
        }

        int doubleParented = -1;
        int lastParent = -1;
        // Casos em que a aresta extra é entre nós não-raiz
        foreach(int[] e in edges){
            // SetHasChild(e[0]);
            if(!HasParent(e[1])){
                SetParent(e[1], e[0]);
                continue;
            }
            doubleParented = e[1];
            lastParent= e[0];
        }
        // verificar se foi formado um ciclo
        if(doubleParented != -1){
            int n = GetParent(doubleParented);
            bool cycle = false;
            while(HasParent(n)){
                if(GetParent(n) == doubleParented){
                    cycle = true;
                    break;
                }
                n = GetParent(n);
            }
            if(cycle) return [GetParent(doubleParented), doubleParented];
            return [lastParent, doubleParented];
        }

        // Casos em que a aresta extra aponta ao nó raiz
        // Console.WriteLine("Yell Heah");
        ArrayList ancestry = new ArrayList();

        ancestry.Add(1);

        int ind;
        int lastAdded = 1;
        while(true){
            ind = ancestry.IndexOf(GetParent(lastAdded));
            if(ind != -1){
                break;
            }

            int parent = GetParent(lastAdded);
            ancestry.Add(parent);
            lastAdded = parent;
        }

        // Console.WriteLine(ind);
        // foreach(var v in ancestry) Console.WriteLine(v);

        int[] r = new int[2];
        foreach(int[] e in edges.Reverse()){
            // Console.WriteLine(ancestry.IndexOf(e[0]) + " - " + ancestry.IndexOf(e[1]));
            if(ancestry.IndexOf(e[0]) >= ind 
            && ancestry.IndexOf(e[1]) >= ind) {
                r[0] = e[0];
                r[1] = e[1];
                break;
            }
        }


        return r;
    }

    private int[] par = new int[1001];
    // private bool[] chi = new bool[1000];
    private bool HasParent(int num){
        return par[num] != -1;
    }

    private void SetParent(int num, int parent){
        par[num] = parent;
    }
    private int GetParent(int num){
        return par[num];
    }
    // private bool HasChild(int num){
    //     return chi[num];
    // }

    // private void SetHasChild(int num){
    //     chi[num] = true;
}
