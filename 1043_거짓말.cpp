#include <stdio.h>
int N, M, rp;

int visit[51]; // DFS 시 이미 탐색한 인원 탐색 X
int visit_party[51]; // DFS 시 이미 탐색한 Party 탐색 X
int truth; // 진실만 말해야하는 Party 숫자
struct LinkedList {
	int idx;
	LinkedList* next;
};
LinkedList heap[1000]; // LinkedList 메모리 미리 잡아둠
LinkedList* Party[51]; // 50번 Party 까지 참가자 번호 삽입
LinkedList* Person[51]; // 50번 인원까지 참가한 Party 번호 삽입
LinkedList* LiePerson; // 처음에 거짓말 아는 사람들 목록 삽입

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
	LinkedList* party_list = Person[person]; // 해당 인원이 참가한 Party List 번호
	while (party_list != 0) {
		int party_idx = party_list->idx; // Party List 번호 꺼냄

		if (visit_party[party_idx] == 0) { // 탐색한 Party 번호 아닐 경우에만
			visit_party[party_idx] = 1; // 탐색 했음 표시
			truth++; // 진실만 말해야하는 Party 번호로 하나 추가

			LinkedList* person_list = Party[party_idx]; // 해당 Party에 참가한 인원 List 번호
			while (person_list != 0) {
				int person_idx = person_list->idx;

				if (visit[person_idx] == 0) {
					visit[person_idx] = 1; // 탐색한 인원 아닐때에만

					DFS(person_idx); // DFS 수행
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
		LiePerson = addListNode(k, LiePerson); // 거짓말 쟁이라는 것 아는 사람 List
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
	LinkedList* temp = LiePerson; // 거짓말 쟁이라는 것 아는 사람들 List 에서 진실만 말해야하는 Party 탐색 수행
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