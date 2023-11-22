# red_black_tree

Reprezentacja drzewa dla 12 losowych elementów:
```
{
	height: 5,
	size: 12,
	root: 0x55ff24f96f30,
	values inorder: [  37, 88, 193, 247, 323, 458, 680, 841, 852, 870, 871, 873  ],
	values preorder: [  680, 88, 37, 323, 247, 193, 458, 870, 852, 841, 873, 871  ],
	nodes: [
		[2] = {data: 680, parent: 0, left child: 0x55ff24f97030 ([6]), right child: 0x55ff24f96f70 ([3]), color: "red"}
		[6] = {data: 88, parent: 0x55ff24f96f30 ([2]), left child: 0x55ff24f96ff0 ([5]), right child: 0x55ff24f97070 ([7]), color: "black"}
		[5] = {data: 37, parent: 0x55ff24f97030 ([6]), left child: 0, right child: 0, color: "black"}
		[7] = {data: 323, parent: 0x55ff24f97030 ([6]), left child: 0x55ff24f97130 ([10]), right child: 0x55ff24f96eb0 ([0]), color: "red"}
		[10] = {data: 247, parent: 0x55ff24f97070 ([7]), left child: 0x55ff24f97170 ([11]), right child: 0, color: "black"}
		[11] = {data: 193, parent: 0x55ff24f97130 ([10]), left child: 0, right child: 0, color: "red"}
		[0] = {data: 458, parent: 0x55ff24f97070 ([7]), left child: 0, right child: 0, color: "black"}
		[3] = {data: 870, parent: 0x55ff24f96f30 ([2]), left child: 0x55ff24f96fb0 ([4]), right child: 0x55ff24f96ef0 ([1]), color: "black"}
		[4] = {data: 852, parent: 0x55ff24f96f70 ([3]), left child: 0x55ff24f970f0 ([9]), right child: 0, color: "black"}
		[9] = {data: 841, parent: 0x55ff24f96fb0 ([4]), left child: 0, right child: 0, color: "red"}
		[1] = {data: 873, parent: 0x55ff24f96f70 ([3]), left child: 0x55ff24f970b0 ([8]), right child: 0, color: "black"}
		[8] = {data: 871, parent: 0x55ff24f96ef0 ([1]), left child: 0, right child: 0, color: "red"}
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
