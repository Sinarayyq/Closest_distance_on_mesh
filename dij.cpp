#include <dijkstra.h>


// 示例类：边的结构体(用来演示)
class EData
{
public:
	int start; // 边的起点
	int end;   // 边的终点
	double weight; // 边的权重

public:
	EData() {}
	EData(int s, int e, double w) :start(s), end(e), weight(w) {}
};

// 邻接表
class ListUDG
{
#define MAX 5000
#define INF         (~(0x1<<31))        // 最大值(即0X7FFFFFFF)
private: // 内部类

	class ENode             // 邻接表中表对应的链表的顶点
	{
		int ivex;           // 该边所指向的顶点的位置
		double weight;         // 该边的权
		ENode *nextEdge;    // 指向下一条弧的指针
		friend class ListUDG;
	};


	class VNode             // 邻接表中表的顶点
	{
		int data;          // 顶点信息
		ENode *firstEdge;   // 指向第一条依附该顶点的弧
		friend class ListUDG;
	};

private: // 私有成员
	int mVexNum;             // 图的顶点的数目
	int mEdgNum;             // 图的边的数目
	VNode mVexs[MAX];

public:
	// 创建邻接表对应的图(自己输入)
	//ListUDG();
	// 创建邻接表对应的图(用已提供的数据)
	ListUDG(int vexs[], int vlen, EData *edges[], int elen);
	~ListUDG();

	void dijkstra(int vs, int vexs[], double dist[]);


private:

	// 返回ch的位置
	int getPosition(int ch);

	// 将node节点链接到list的最后
	void linkLast(ENode *list, ENode *node);
	// 获取边<start, end>的权值；若start和end不是连通的，则返回无穷大。
	double getWeight(int start, int end);

};

///*
//* 创建邻接表对应的图(自己输入)
//*/
//ListUDG::ListUDG()
//{
//	char c1, c2;
//	int v, e;
//	int i, p1, p2;
//	int weight;
//	ENode *node1, *node2;
//
//	// 输入"顶点数"和"边数"
//	std::cout << "input vertex number: ";
//	std::cin >> mVexNum;
//	std::cout << "input edge number: ";
//	std::cin >> mEdgNum;
//	if (mVexNum < 1 || mEdgNum < 1 || (mEdgNum >(mVexNum * (mVexNum - 1))))
//	{
//		std::cout << "input error: invalid parameters!" << std::endl;
//		return;
//	}
//
//	// 初始化"邻接表"的顶点
//	for (i = 0; i<mVexNum; i++)
//	{
//		std::cout << "vertex(" << i << "): ";
//		mVexs[i].data = readChar();
//		mVexs[i].firstEdge = NULL;
//	}
//
//	// 初始化"邻接表"的边
//	for (i = 0; i<mEdgNum; i++)
//	{
//		// 读取边的起始顶点和结束顶点
//		std::cout << "edge(" << i << "): ";
//		c1 = readChar();
//		c2 = readChar();
//		std::cin >> weight;
//
//		p1 = getPosition(c1);
//		p2 = getPosition(c2);
//		// 初始化node1
//		node1 = new ENode();
//		node1->ivex = p2;
//		node1->weight = weight;
//		// 将node1链接到"p1所在链表的末尾"
//		if (mVexs[p1].firstEdge == NULL)
//			mVexs[p1].firstEdge = node1;
//		else
//			linkLast(mVexs[p1].firstEdge, node1);
//		// 初始化node2
//		node2 = new ENode();
//		node2->ivex = p1;
//		node2->weight = weight;
//		// 将node2链接到"p2所在链表的末尾"
//		if (mVexs[p2].firstEdge == NULL)
//			mVexs[p2].firstEdge = node2;
//		else
//			linkLast(mVexs[p2].firstEdge, node2);
//	}
//}

/*
* 创建邻接表对应的图(用已提供的数据)
*/
ListUDG::ListUDG(int vexs[], int vlen, EData *edges[], int elen)
{
	int c1, c2;
	int i, p1, p2;
	double weight;
	ENode *node1, *node2;

	// 初始化"顶点数"和"边数"
	mVexNum = vlen;
	mEdgNum = elen;
	// 初始化"邻接表"的顶点
	for (i = 0; i<mVexNum; i++)
	{
		mVexs[i].data = vexs[i];
		mVexs[i].firstEdge = NULL;
	}

	// 初始化"邻接表"的边
	for (i = 0; i<mEdgNum; i++)
	{
		// 读取边的起始顶点和结束顶点
		c1 = edges[i]->start;
		c2 = edges[i]->end;
		weight = edges[i]->weight;

		p1 = getPosition(c1);
		p2 = getPosition(c2);
		// 初始化node1
		node1 = new ENode();
		node1->ivex = p2;
		node1->weight = weight;
		// 将node1链接到"p1所在链表的末尾"
		if (mVexs[p1].firstEdge == NULL)
			mVexs[p1].firstEdge = node1;
		else
			linkLast(mVexs[p1].firstEdge, node1);
		// 初始化node2
		node2 = new ENode();
		node2->ivex = p1;
		node2->weight = weight;
		// 将node2链接到"p2所在链表的末尾"
		if (mVexs[p2].firstEdge == NULL)
			mVexs[p2].firstEdge = node2;
		else
			linkLast(mVexs[p2].firstEdge, node2);
	}
}

/*
* 析构函数
*/
ListUDG::~ListUDG()
{
}

/*
* 将node节点链接到list的最后
*/
void ListUDG::linkLast(ENode *list, ENode *node)
{
	ENode *p = list;

	while (p->nextEdge)
		p = p->nextEdge;
	p->nextEdge = node;
}

/*
* 返回ch的位置
*/
int ListUDG::getPosition(int ch)
{
	int i;
	for (i = 0; i<mVexNum; i++)
		if (mVexs[i].data == ch)
			return i;
	return -1;
}

/*
* 获取边<start, end>的权值；若start和end不是连通的，则返回无穷大。
*/
double ListUDG::getWeight(int start, int end)
{
	ENode *node;

	if (start == end)
		return 0;

	node = mVexs[start].firstEdge;
	while (node != NULL)
	{
		if (end == node->ivex)
			return node->weight;
		node = node->nextEdge;
	}

	return INF;
}

/*
* Dijkstra最短路径。
* 即，统计图中"顶点vs"到其它各个顶点的最短路径。
*
* 参数说明：
*       vs -- 起始顶点(start vertex)。即计算"顶点vs"到其它顶点的最短路径。
*     prev -- 前驱顶点数组。即，prev[i]的值是"顶点vs"到"顶点i"的最短路径所经历的全部顶点中，位于"顶点i"之前的那个顶点。
*     dist -- 长度数组。即，dist[i]是"顶点vs"到"顶点i"的最短路径的长度。
*/
void ListUDG::dijkstra(int vs, int prev[], double dist[])
{
	int i, j, k;
	double min;
	double tmp;
	int flag[MAX];      // flag[i]=1表示"顶点vs"到"顶点i"的最短路径已成功获取。

	// 初始化
	for (i = 0; i < mVexNum; i++)
	{
		flag[i] = 0;                // 顶点i的最短路径还没获取到。
		prev[i] = 0;                // 顶点i的前驱顶点为0。
		dist[i] = getWeight(vs, i);  // 顶点i的最短路径为"顶点vs"到"顶点i"的权。
	}

	// 对"顶点vs"自身进行初始化
	flag[vs] = 1;
	dist[vs] = 0;

	// 遍历mVexNum-1次；每次找出一个顶点的最短路径。
	for (i = 1; i < mVexNum; i++)
	{
		// 寻找当前最小的路径；
		// 即，在未获取最短路径的顶点中，找到离vs最近的顶点(k)。
		min = INF;
		for (j = 0; j < mVexNum; j++)
		{
			if (flag[j] == 0 && dist[j]<min)
			{
				min = dist[j];
				k = j;
			}
		}
		// 标记"顶点k"为已经获取到最短路径
		flag[k] = 1;

		// 修正当前最短路径和前驱顶点
		// 即，当已经"顶点k的最短路径"之后，更新"未获取最短路径的顶点的最短路径和前驱顶点"。
		for (j = 0; j < mVexNum; j++)
		{
			tmp = getWeight(k, j);
			tmp = (tmp == INF ? INF : (min + tmp)); // 防止溢出
			if (flag[j] == 0 && (tmp  < dist[j]))
			{
				dist[j] = tmp;
				prev[j] = k;
			}
		}
	}

	// 打印dijkstra最短路径的结果
	std::cout << "dijkstra(" << mVexs[vs].data << "): " << std::endl;
	for (i = 0; i < mVexNum; i++)
		std::cout << "  shortest(" << mVexs[vs].data << ", " << mVexs[i].data << ")=" << dist[i] << std::endl;
}


int DijkstraAlgorithm(OpenMesh_Mesh mesh, std::vector<point> subsampled_points, OpenMesh_Mesh::Point start_point, std::vector<std::vector<double>> *distance)
{
	size_t size = subsampled_points.size();

	std::vector<OpenMesh_Mesh::Point> point_openmesh;
	for (int i = 0; i < size; ++i)
	{
		point_openmesh.push_back(OpenMesh_Mesh::Point(boost::get<0>(subsampled_points[i]), boost::get<1>(subsampled_points[i]), boost::get<2>(subsampled_points[i])));
	}

	return 0;
}

int DijkstraAlgorithm(OpenMesh_Mesh mesh, std::vector<OpenMesh_Mesh::Point> subsampled_points, OpenMesh_Mesh::Point start_point, std::vector<std::vector<double>> *distance)
{
	/*size_t size_points_on_mesh = mesh.number_of_vertices();
	size_t size_edges = mesh.edges().size();*/
	size_t size_points_on_mesh = mesh.n_vertices();
	size_t size_edges = mesh.n_edges();
	//OpenMesh_Mesh  m;

	int prev[MAX] = { 0 };
	double dist[MAX] = { 0 };

	// 顶点
	//char vexs[] = { '0', '1', '2', '3', '4', '5', '16' };
	int *vexs = new int[size_points_on_mesh];
	for (int i = 0; i < size_points_on_mesh; i++)
	{
		vexs[i] = i;
		//std::cout << vexs[i] << std::endl;
	}

	//weight
	int count = 0;
	//EData* edges_temp = new EData[size_edges];
	EData **edges;
	edges = (EData **)malloc(size_edges * sizeof(EData *));
	/*for (edge_iterator it = mesh.edges_begin(); it != mesh.edges_end(); ++it)
	{
	vertex_descriptor s = mesh.vertex((*it), 0);
	vertex_descriptor t = mesh.vertex((*it), 1);
	edges[count] = (EData *)malloc(sizeof(EData));
	edges[count]->start = (int)s;
	edges[count]->end = (int)t;
	edges[count]->weight = sqrt((mesh.point(s) - mesh.point(t)).squared_length());
	count++;
	}*/
	for (OpenMesh_Mesh::EdgeIter it = mesh.edges_begin(); it != mesh.edges_end(); ++it)
	{
		OpenMesh_Mesh::VertexHandle s = mesh.to_vertex_handle(mesh.halfedge_handle(it, 0));
		OpenMesh_Mesh::VertexHandle t = mesh.from_vertex_handle(mesh.halfedge_handle(it, 0));
		edges[count] = (EData *)malloc(sizeof(EData));
		edges[count]->start = s.idx();
		edges[count]->end = t.idx();
		edges[count]->weight = mesh.calc_edge_sqr_length(it.handle());
		count++;
	}

	/*for (int i = 0; i < size_edges; i++)
	{
	edges[i] = &(edges_temp[i]);
	}*/

	// 边
	//EData *edges[] = {
	//	// 起点 终点 权
	//	new EData('0', '1', 12),
	//	new EData('0', '5', 16),
	//	new EData('0', '16', 14),
	//	new EData('1', '2', 10),
	//	new EData('1', '5',  7),
	//	new EData('2', '3',  3),
	//	new EData('2', '4',  5),
	//	new EData('2', '5',  6),
	//	new EData('3', '4',  4),
	//	new EData('4', '5',  2),
	//	new EData('4', '16',  8),
	//	new EData('5', '16',  9),
	//};
	/*int vlen = sizeof(vexs) / sizeof(vexs[0]);
	int elen = sizeof(edges) / sizeof(edges[0]);*/

	int vlen = (int)size_points_on_mesh;
	int elen = (int)size_edges;
	ListUDG* pG;

	// 自定义"图"(输入矩阵队列)
	//pG = new ListUDG();
	// 采用已有的"图"
	pG = new ListUDG(vexs, vlen, edges, elen);

	size_t size_subsampled_points = subsampled_points.size();
	int no_start_point = 0;
	for (int i = 0; i < size_points_on_mesh; i++)
	{
		if (start_point == mesh.point(mesh.vertex_handle(i)))
		{
			break;
		}
		no_start_point++;
	}

	/*for (vertex_iterator it = mesh.vertices_begin(); it != mesh.vertices_end(); ++it)
	{
	if (start_point == mesh.point((*it)))
	{
	break;
	}
	no_start_point++;
	}*/
	// dijkstra算法获取start point到其它各个顶点的最短距离
	pG->dijkstra(no_start_point, prev, dist);

	//std::vector<std::vector<double>> distance;
	(*distance).resize(size_subsampled_points);
	for (int i = 0; i < size_subsampled_points; i++)
	{
		(*distance)[i].resize(2);
		int number = 0;
		for (int j = 0; j < size_points_on_mesh; j++)
		{
			if (subsampled_points[i] == mesh.point(mesh.vertex_handle(i)))
			{
				(*distance)[i][1] = i;
				(*distance)[i][0] = dist[number];
			}
			number++;
		}
	}

	/*for (int i = 0; i < size_subsampled_points; i++)
	{
	(*distance)[i].resize(2);
	int number = 0;
	for (vertex_iterator it = mesh.vertices_begin(); it != mesh.vertices_end(); ++it)
	{
	if (mesh.point((*it)) == subsampled_points[i])
	{
	(*distance)[i][1] = i;
	(*distance)[i][0] = dist[number];
	}
	number++;
	}
	}*/
	std::sort((*distance).begin(), (*distance).end());
	//std::vector<Point, double> distance;
	//for (int i = 0; i < size_subsampled_points; i++)
	//{
	//distance.push_back(subsampled_points[temp_dist[i][1]], temp_dist[i][0]);
	//}

	// floyd算法获取各个顶点之间的最短距离
	//pG->floyd(path, floy);
	//Visualizer(points_on_mesh, subsampled_points, *distance);

	return 0;
}