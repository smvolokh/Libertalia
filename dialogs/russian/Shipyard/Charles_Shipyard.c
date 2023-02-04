// ������ �� �������
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("����� �������?", "��� ��� ������?"), "������ ������� �� �������� ������ ��� ������...", "� ���� �� �����, � � ������ � ������, � ����� ����������� �������������� �� �����.",
                          "�� ��� �� �������? ��� ���� - ������� �������, ������� ���� � ��������.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("� "+ GetSexPhrase("���������","����������") +"...", "������ ��� �� � ��� ��������."), "��, ���-�� � ������� ���� �����...",
                      "��, ������...", "�������...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason ��������� �������
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_2")
            {
                link.l1 = "����������, ������, ��� �� ������� �������... � �������������� � ��������� ������... � ������� ���������� ��� �������... ������� �� ��������������?";
                link.l1.go = "mtraxx";
			}
		break;
		
		// Addon 2016-1 Jason ��������� �������
		case "mtraxx":
            dialog.text = "������-�� ��������� �� ��������, ������... �������-�� ��������� � ����� - ��� � ��� �� ��� �� �����������? � �� �������, � �� �������� ������ � �� ���������� ������.";
			link.l1 = "� ����, � ���� ����� ����� ����! ���� ���� � ����������� �����. �� ����, ��� ��� ��������, ������������� ����� ������ ������, ������� �������� �������� �����...";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "� �� ������ ��������, �� � ��� � ���������, ���� �� �� �� �����. �� ������ ���������� ��� ���������� � ��� ����������� ����? ����������, ����� ����� ������. �� ���� ��� � ���: ����� ������������� �� ���� ������ ���������������� ��������, ����� ����� � ��� ��������. �� ���������, � ��� �? ��� �� ��������� ��������, � �� ���� ������ �������, ����� �������� ��������� ������������� �����. � � ��� �� ������� � ������� �� �������. ������, ��� ����� ����� ������ �������, �, �������� �� ��� ������ �� ��������, � �� ��������� �������� � ���� ������. ��� ������������ ��������� ��������� � ���. � ���� ��� �� �����, ���!";
			link.l1 = "��. ����. ��, ������� ��� ���� ���������, ������. �����!";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            DialogExit();
			AddQuestRecord("Roger_2", "4");
			pchar.questTemp.Mtraxx = "silk_3";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // ���� ���-�� ����� ������ switch  �� return �� ������ ������� �����
}

