#pragma once

enum Permissions
{
	none = 0,
	attack = 1 << 0,  // ���� ���������
	defence = 1 << 1,  // ���� ����������
	take = 1 << 2,  // ���� �����
	toss = 1 << 3,  // ���� ��������
	discard = 1 << 4  // �������� ����
};
