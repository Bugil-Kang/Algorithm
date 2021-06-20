#include <stdio.h>
int N, M, rp;

int visit[51]; // DFS �� �̹� Ž���� �ο� Ž�� X
int visit_party[51]; // DFS �� �̹� Ž���� Party Ž�� X
int truth; // ���Ǹ� ���ؾ��ϴ� Party ����
struct LinkedList {
	int idx;
	LinkedList* next;
};
LinkedList heap[1000]; // LinkedList �޸� �̸� ��Ƶ�
LinkedList* Party[51]; // 50�� Party ���� ������ ��ȣ ����
LinkedList* Person[51]; // 50�� �ο����� ������ Party ��ȣ ����
LinkedList* LiePerson; // ó���� ������ �ƴ� ����� ��� ����

LinkedList* addListNode(int idx, LinkedList* head) {
	LinkedList* node = &heap[rp++];
	node->idx = idx;
	node->next = head;
	return node;
}

void Init() {
	for (int i = 0; i <= 50; i++) {
		Party[i] = Person[i] = 0;
		visit[i] = visit_party[i] = 0;
	}
	rp = 0;
	LiePerson = 0;
}

void DFS(int person) {
	LinkedList* party_list = Person[person]; // �ش� �ο��� ������ Party List ��ȣ
	while (party_list != 0) {
		int party_idx = party_list->idx; // Party List ��ȣ ����

		if (visit_party[party_idx] == 0) { // Ž���� Party ��ȣ �ƴ� ��쿡��
			visit_party[party_idx] = 1; // Ž�� ���� ǥ��
			truth++; // ���Ǹ� ���ؾ��ϴ� Party ��ȣ�� �ϳ� �߰�

			LinkedList* person_list = Party[party_idx]; // �ش� Party�� ������ �ο� List ��ȣ
			while (person_list != 0) {
				int person_idx = person_list->idx;

				if (visit[person_idx] == 0) {
					visit[person_idx] = 1; // Ž���� �ο� �ƴҶ�����

					DFS(person_idx); // DFS ����
				}
				person_list = person_list->next;
			}
		}
		party_list = party_list->next;
	}
}

int main() {
	Init();
	scanf("%d %d", &N, &M);

	int lie_num;
	scanf("%d", &lie_num);
	for (int i = 0; i < lie_num; i++) {
		int k;
		scanf("%d", &k);
		LiePerson = addListNode(k, LiePerson); // ������ ���̶�� �� �ƴ� ��� List
	}

	for (int i = 1; i <= M; i++) {
		int k;
		scanf("%d", &k);

		for (int j = 0; j < k; j++) {
			int p;
			scanf("%d", &p);

			Party[i] = addListNode(p, Party[i]);
			Person[p] = addListNode(i, Person[p]);
		}
	}

	truth = 0;
	LinkedList* temp = LiePerson; // ������ ���̶�� �� �ƴ� ����� List ���� ���Ǹ� ���ؾ��ϴ� Party Ž�� ����
	while (temp != 0) {
		int idx = temp->idx;

		if (visit[idx] == 0) {
			visit[idx] = 1;
			DFS(idx);
		}

		temp = temp->next;
	}
	printf("%d", M - truth);
	return 0;
}