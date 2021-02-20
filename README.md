<!-- [![Work in Repl.it](https://classroom.github.com/assets/work-in-replit-14baed9a392b3a25080506f3b7b6d57f295ec2978f6f33ec97e36a161684cbe9.svg)](https://classroom.github.com/online_ide?assignment_repo_id=3489414&assignment_repo_type=AssignmentRepo) -->
# Assignment2
## Q1: Developing a trie data structure
### Performance of different locking mechanisms on different workloads
<img src="Q1/plots/graph.png" alt="Performance on differnt workloads">

## Q2: Implementing caching policies
### Hit Rate graph
<img src="Q2/plots/hr_graph.png" alt="Hit Rate Graph">

### Timing Analysis
<img src="Q2/plots/tm_graph.png" alt="Timing Graph">

## Files
<pre>├── <font color="#3465A4"><b>Q1</b></font>
│   ├── graph.py
│   ├── Makefile
│   ├── OUTPUT.txt
│   ├── <font color="#3465A4"><b>plots</b></font>
│   │   └── <font color="#75507B"><b>graph.png</b></font>
│   ├── plots.md
│   ├── README.md
│   ├── <font color="#3465A4"><b>tests</b></font>
│   │   ├── <font color="#3465A4"><b>multi_thread</b></font>
│   │   │   ├── <font color="#3465A4"><b>find</b></font>
│   │   │   │   ├── 1.txt
│   │   │   │   ├── 2.txt
│   │   │   │   ├── 3.txt
│   │   │   │   ├── exp_find_1.txt
│   │   │   │   ├── exp_find_2.txt
│   │   │   │   └── exp_find_3.txt
│   │   │   ├── <font color="#3465A4"><b>initial</b></font>
│   │   │   │   ├── 1.txt
│   │   │   │   ├── 2.txt
│   │   │   │   ├── 3.txt
│   │   │   │   └── exp_ins.txt
│   │   │   ├── <font color="#3465A4"><b>pref</b></font>
│   │   │   │   ├── 1.txt
│   │   │   │   ├── 2.txt
│   │   │   │   ├── 3.txt
│   │   │   │   ├── exp_1.txt
│   │   │   │   ├── exp_2.txt
│   │   │   │   └── exp_3.txt
│   │   │   └── <font color="#3465A4"><b>rem</b></font>
│   │   │       ├── 1.txt
│   │   │       ├── 2.txt
│   │   │       ├── 3.txt
│   │   │       └── exp.txt
│   │   └── <font color="#3465A4"><b>single_thread</b></font>
│   │       ├── exp_ins.txt
│   │       ├── exp_rem.txt
│   │       ├── find_test_exp.txt
│   │       ├── find_test.txt
│   │       ├── initial.txt
│   │       ├── pref_text_exp.txt
│   │       ├── pref_text.txt
│   │       └── rem_list.txt
│   ├── test_trie_single_threaded.c
│   ├── test_trie_s_lock.c
│   ├── trie.c
│   ├── trie.h
│   ├── wl_hoh_lock.c
│   ├── wl_rw_lock.c
│   ├── wl_s_lock.c
│   ├── words.txt
│   └── workload.c
├── <font color="#3465A4"><b>Q2</b></font>
│   ├── definitions.h
│   ├── hr_graph.py
│   ├── main.c
│   ├── Makefile
│   ├── perf_graph.py
│   ├── <font color="#3465A4"><b>plots</b></font>
│   │   ├── <font color="#75507B"><b>hr_graph.png</b></font>
│   │   └── <font color="#75507B"><b>tm_graph.png</b></font>
│   ├── policy.c
│   ├── queue.c
│   ├── README.md
│   ├── Solutions.md
│   └── workload.c
└── README.md
</pre>

## How to run?
> Read the Makefile in both of the folders