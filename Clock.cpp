#include <iostream>
#include <vector>

using namespace std;

const vector<vector<int>> switches = { //10���� ����ġ�� ���� �� �� �ð�� ����Ǿ��ִ��� ��Ÿ���� �迭. �������� �־��� ��������.
	{0, 1, 2}, //#0
	{3, 7, 9, 11}, //#1
	{4, 10, 14, 15}, //#2
	{0, 4, 5, 6, 7}, //#3
	{6, 7, 8, 10, 12}, //#4
	{0, 2, 14, 15}, //#5
	{3, 14, 15}, //#6
	{4, 5, 7, 14, 15}, //#7
	{1, 2, 3, 4, 5}, //#8
	{3, 4, 5, 9, 13}, //#9
};

int difference_clock(vector<int>& clocks, int a, int b) //�� �ð� ������ �ð� ���̸� �����
{
	int difference = 0;

	if (clocks[a] > clocks[b])
		return clocks[a] - clocks[b];
	else return clocks[b] - clocks[a];
}

int countswitch(vector<int>& clocks)
{
	int result = 0; // -1�̸� �޼� �Ұ���
	int select_clock = -1;
	bool finished = true; //�������� Ƚ���� �������� false, �Ϸ��ϸ� true
	vector<int> pressed;
	int cycle[10];

	//�Ϸ�����: �ð谡 ��� 12�ø� �Ϸ�.
	for (int i = 0; i < clocks.size(); ++i)
	{
		if (clocks[i] != 12)
			finished = false;
	}
	if (finished) return result;

	//�Ұ����� ����
	if (clocks[8] != clocks[12]) //8�� �ð�� 12�� �ð谡 ���� �ٸ��� ���� 12�÷� ���� �� ����
		return -1;

	if (difference_clock(clocks, 9, 13) != difference_clock(clocks, 11, 13))//9 - 13�̶� 11 - 13�� ���� ������ 12�÷� ���� �� ����
		return -1;

	//�Ұ����� ����2 : ����Ŭ�� �����ϸ� �Ұ�����.
	for (int i = 0; i < pressed.size(); ++i) 
	{
		++cycle[pressed[i]];
	}

	for (int i = 0; i < 10; ++i)			//���� ����ġ�� 4�� �̻� ������ �Ǹ� ����Ŭ�� �����Ѵٴ� ��
	{
		if (cycle[i] >= 4)
		{
			return -1;
			break;
		}
	}

	//12�÷� ���� �ð� ����
	for (int i = 0; i < clocks.size(); ++i)
	{
		if (clocks[i] != 12)
			select_clock = i;
	}

	//����ġ�� �� �� ������ �� ���� ���¸� ��� ȣ��
	for (int num_switch = 0; num_switch < 10; ++num_switch)
	{
		for (int i = 0; i < switches[num_switch].size(); ++i)
		{
			if(clocks[switches[num_switch][i]] < 12)
				clocks[switches[num_switch][i]] += 3;
			else clocks[switches[num_switch][i]] = 3;

			result += 1;
		}

		result += countswitch(clocks);
		
	}

	return result;
}



int main()
{
	const int INF = 987654321;
	int num_case, c;
	int answer = -1;

	vector<int> inVector, clocks;

	cin >> num_case;

	while (cin >> c)
	{
		inVector.push_back(c);
	}

	//�Է� ���� �κ�
	/*
	cout << "inVector:";

	for (int i = 0; i < inVector.size(); ++i)
		cout << inVector[i];

	cout << endl << "num_case:" << num_case << endl;
	*/

	for (int i = 0; i < num_case; ++i)
	{
		//cout << "clocks:";
		for (int j = 16 * i; j < 16 * (i + 1); ++j)
		{
			clocks.push_back(inVector[i]);
			//clocks ����
			//cout << clocks[i];
		}
		//cout << endl;

		answer = countswitch(clocks);
		cout << answer << endl;
	}
	return 0;
}