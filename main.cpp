// 8 puzzle BFS
#include <iostream>
#include <queue>
#include <sstream>
#include <set>

using namespace std;

struct Node

{
	Node* p;
	int matrix_val[3][3],
	x,y,
	misplacedNr;
    string status;



};

Node* create_node(int matrix_val[3][3], int x, int y, int x1, int y1, Node* p)
{
	Node* n_val = new Node;
	n_val->p = p;
	memcpy(n_val->matrix_val, matrix_val, sizeof n_val->matrix_val);
	swap(n_val->matrix_val[x][y], n_val->matrix_val[x1][y1]);
	n_val->misplacedNr = INT_MAX;
	n_val->x = x1;
	n_val->y = y1;

	return n_val;
}


int displayPuzzle(int matrix_val[3][3])
{
	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<3; j++)
			printf("%d ", matrix_val[i][j]);
		printf("\n");
	}
	return 0;
}

int compute_misplacedNr(int initial_state[3][3], int goal_state[3][3])
{

	int misplacedNr_val = 0, i, j;
	for (i = 0; i<3; i++)
		for (j = 0; j<3; j++) {
			if (initial_state[i][j] && initial_state[i][j] != goal_state[i][j]) {
                misplacedNr_val++;
			}
		}
	return misplacedNr_val;

}

int legal_move(int x, int y)
{
	return (x >= 0 && x < 3 && y >= 0 && y < 3);
}


void displayPath(Node* root)
{
	if (root == nullptr)
		return;
	displayPath(root->p);
	displayPuzzle(root->matrix_val);
	printf("\n");

}


set<string> visited;
void eight_bfs(int initial[3][3], int x, int y, int goal[3][3])
{

	queue<Node*>  q;
	Node* root = create_node(initial, x, y, x, y, nullptr);
    root->misplacedNr = compute_misplacedNr(initial, goal);
    //cout << "root misplacedNr =" << root->misplacedNr << endl << "------------------------" << endl << endl;
	q.push(root);


	while (!q.empty())
	{

        //cout << "queue size=" << q.size() << endl;
		Node* currentNode = q.front();
		q.pop();
		//cout << " <------->   currentNode->misplacedNr : " << currentNode->misplacedNr << endl;

		if (currentNode->misplacedNr == 0) //check if the current matrix is the solution
        {
			displayPath(currentNode);
			return;
		}

		int i = 0;
		// down, left, up, right movements of the '0'
        int row[] = { 1, 0, -1, 0 };
        int col[] = { 0, -1, 0, 1 };

		while (i<4){
			if (legal_move(currentNode->x + row[i], currentNode->y + col[i])) {

				Node* nod = create_node(currentNode->matrix_val, currentNode->x, currentNode->y, currentNode->x + row[i],
                                            currentNode->y + col[i], currentNode);
                nod->misplacedNr = compute_misplacedNr(nod->matrix_val, goal);
                //cout << "misplacedNr=" << nod->misplacedNr << endl;
				//nod->status = seeStatus(nod->mat);
				string str = "";

				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++) {

						stringstream ss;
						ss << nod->matrix_val[i][j];
						string s;
						ss >> s;
						str = str + s;
					}



				if (visited.find(str) == visited.end()) {
					nod->status = str;
					//cout << "child created for " << " i=" << i << endl;
					//cout << "visited node: " << nod->status << endl;
					visited.insert(str);
					q.push(nod);

				}


			}
			else {
				//cout << " >>>>> for " << i << " is not safe, so no child is created" << endl;
			}
			i++;
		}
	}
}


int main() {
    int x = 1, y = 2; //row and col of the '0' in the initial state matrix
    int initial_state[3][3] = { { 1, 2, 5 }, { 3, 4, 0 },{ 6, 7, 8 } };
    int goal_state[3][3] = { { 0, 1, 2 },{ 3, 4, 5 },{ 6, 7, 8 } };


	eight_bfs(initial_state, x, y, goal_state);

	return 0;

}




