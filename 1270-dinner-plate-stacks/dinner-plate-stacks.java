class DinnerPlates {

    List<Stack<Integer>> lt;
    TreeSet<Integer> set;
    int capacity;

    public DinnerPlates(int capacity) {
        set = new TreeSet<>();
        this.capacity = capacity;
        lt = new ArrayList<>();
    }

    public void push(int val) {
        while (!set.isEmpty() && set.first() >= lt.size()) {
            set.pollFirst();
        }
        if (set.isEmpty()) {
            lt.add(new Stack<>());
            set.add(lt.size() - 1);
        }

        int idx = set.first();
        Stack<Integer> st = lt.get(idx);
        st.push(val);

        if (st.size() == capacity) {
            set.remove(idx);
        }
    }

    public int pop() {
        while (!lt.isEmpty() && lt.get(lt.size() - 1).isEmpty()) {
            lt.remove(lt.size() - 1);
        }

        if (lt.isEmpty()) return -1;

        int idx = lt.size() - 1;
        Stack<Integer> st = lt.get(idx);
        int val = st.pop();

        set.add(idx);

        while (!lt.isEmpty() && lt.get(lt.size() - 1).isEmpty()) {
            set.remove(lt.size() - 1);
            lt.remove(lt.size() - 1);
        }

        return val;
    }

    public int popAtStack(int index) {
        if (index >= lt.size() || lt.get(index).isEmpty()) return -1;
        int ele = lt.get(index).pop();
        set.add(index);
        return ele;
    }
}