# red_black_tree

Reprezentacja drzewa dla 12 losowych elementów:
```
{
	height: 4,
	size: 12,
	root: 0x55edf691cff0,
	values inorder: [  110, 212, 366, 450, 553, 558, 654, 705, 807, 847, 879, 883  ],
	values preorder: [  705, 450, 212, 110, 366, 558, 553, 654, 847, 807, 879, 883  ],
	nodes: [
		[5] = {data: 705, color: "black", parent: 0, left child: 0x55edf691cfb0 ([4]), right child: 0x55edf691cf30 ([2])}
		[4] = {data: 450, color: "red", parent: 0x55edf691cff0 ([5]), left child: 0x55edf691d070 ([7]), right child: 0x55edf691d030 ([6])}
		[7] = {data: 212, color: "black", parent: 0x55edf691cfb0 ([4]), left child: 0x55edf691d170 ([11]), right child: 0x55edf691cef0 ([1])}
		[11] = {data: 110, color: "red", parent: 0x55edf691d070 ([7]), left child: 0, right child: 0}
		[1] = {data: 366, color: "red", parent: 0x55edf691d070 ([7]), left child: 0, right child: 0}
		[6] = {data: 558, color: "black", parent: 0x55edf691cfb0 ([4]), left child: 0x55edf691d130 ([10]), right child: 0x55edf691d0f0 ([9])}
		[10] = {data: 553, color: "red", parent: 0x55edf691d030 ([6]), left child: 0, right child: 0}
		[9] = {data: 654, color: "red", parent: 0x55edf691d030 ([6]), left child: 0, right child: 0}
		[2] = {data: 847, color: "red", parent: 0x55edf691cff0 ([5]), left child: 0x55edf691d0b0 ([8]), right child: 0x55edf691ceb0 ([0])}
		[8] = {data: 807, color: "black", parent: 0x55edf691cf30 ([2]), left child: 0, right child: 0}
		[0] = {data: 879, color: "black", parent: 0x55edf691cf30 ([2]), left child: 0, right child: 0x55edf691cf70 ([3])}
		[3] = {data: 883, color: "red", parent: 0x55edf691ceb0 ([0]), left child: 0, right child: 0}
	]
}
```

Output dla 10000 elementów:
```
Insertion benchmark
Time elapsed: 3ms
Avg time: 0.0003ms

Tree height: 17

Seek benchmark
Time elapsed: 4ms
Found: 45 elements

Process finished with exit code 0
```

Output dla 10^7 elementów:
```
Insertion benchmark
Time elapsed: 8685ms
Avg time: 0.0008685ms

Tree height: 34

Seek benchmark
Time elapsed: 9045ms
Found: 35583 elements

Process finished with exit code 0
```
