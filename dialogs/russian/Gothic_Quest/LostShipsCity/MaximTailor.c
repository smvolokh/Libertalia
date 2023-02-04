#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			dialog.text = "����������� ����� ����� � ������ ����� "+ GetSexPhrase("�������� ��������","������� �������") +". ��� � ���� ���� ������?";
			link.l1 = "������, � ��� ������ ��������. �� ������, ��� �� ������?";
			link.l1.go = "SeekCitizen";
			link.l2 = "���� ������ ���� ������.";
			link.l2.go = "int_quests";
			link.l3 = LinkRandPhrase("���-������ ���������� ��� ����������?", 
				"��� ������ � ������?", "��, � ������������� ��������"+ GetSexPhrase("","�") +" �� ��������� �������...");
			link.l3.go = "rumours_LSCC";
			link.l10 = "������...";
			link.l10.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//���� ��������
		case "SeekCitizen":
			dialog.text = "� ���� �� �����?";
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCCitizen();
			if (sld.id == "none")
			{
				dialog.text = "� �� �������, � ��� �� ��������. ��� ����� ����� ��� � ������� ����� ��������.";
				Link.l1 = "�������. ����� � ��� �������� �������.";
				Link.l1.go = "SeekCitizen_Choice_2";				
				Link.l2 = "�������, � ����� ���"+ GetSexPhrase("","�") +" �����.";
				Link.l2.go = "exit";	
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = "��� ��� �� �!";
					link.l1 = "���� ��, ����� �� ���� ���"+ GetSexPhrase("��","��") +"!";
					link.l1.go = "exit";
					break;
				}				
				if (sld.sex == "man")
				{
					dialog.text = GetFullName(sld) + ", �� � ��� ��������?";
					Link.l1 = "��-��, �����, ��� ��.";
					Link.l1.go = "SeekCitizen_agree";				
					Link.l2 = "���, �� � ���. ����� ��� ��� ������.";
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = GetFullName(sld) + ", �� � ��� ��������?";
					Link.l1 = "���, ������ � ���.";
					Link.l1.go = "SeekCitizen_agree";				
					Link.l2 = "���, �� � ���. ������, ����� � ��� ��� �������� �������.";
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = "������, �� ���� � ������ �� � ��� ����������. �� ��������.";
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
        case "SeekCitizen_Choice_2":
			dialog.text = "����� ������ ��� ��� ��� � �������.";
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
		break;

		case "SeekCitizen_agree":
			sld = &characters[sti(npchar.quest.seekIdx)];
			npchar.quest.seekIdx.where = WhereLSCCCitizen(sld);
			if (npchar.quest.seekIdx.where == "none")
			{
				if (sld.sex == "man")
				{
					dialog.text = LinkRandPhrase("�� ����, ����� ��� �� �����.", "���� ��� �����, ��� ��...", "�� ����� ��� ��� ��������, ��� ��� �� �����.");
					link.l1 = RandPhraseSimple("�������.", "����...");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = LinkRandPhrase("�� ����� �� ��� �������� �����, �������.", "������� �� ����, ��� ��� ������.", "��, � �� ����, ��� ��� ����� ������ ����.");
					link.l1 = RandPhraseSimple("����.", "����...");
					link.l1.go = "exit";
				}
			}
			else
			{
				if (sld.sex == "man")
				{
					if (sld.location == "LostShipsCityy_town")  
					{						
						string Str1 = npchar.location.locator;
						string Str2 = sld.location.locator;
						if (npchar.location == sld.location && strcut(Str1, 0, 5) == strcut(Str2, 0, 5))
						{
							dialog.text = LinkRandPhrase("�� �����, �� ���� �������. ��� ������������.", "��, ��� �� �����, �� ���� �������!", "�� �� ���� �������, �������, ��� �� ��� �� ������"+ GetSexPhrase("","�") +" ���.");
						}
						else
						{
							dialog.text = LinkRandPhrase("� ����� ��� ������ ������� " + npchar.quest.seekIdx.where + ".", "������� �������� ��� " + npchar.quest.seekIdx.where + ". ��� ��� ��� ��� ���.", "��������� � ����, ������ �� ��������� " + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase("��� �� �����, " + npchar.quest.seekIdx.where + ". ������ ������������.", "��� ���� �� �����, ����� ���!", "���� �� ��������? �� �� ����� ���������.");
						}
						else
						{
							dialog.text = LinkRandPhrase("� ����� ��� ������ ������� " + npchar.quest.seekIdx.where + ".", "������� �������� ��� " + npchar.quest.seekIdx.where + ". ��� ��� ��� ��� ���.", "��������� � ����, ������ �� ��������� " + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple("���, �������. ������� ����, ��������.", "������� ����!");
					link.l1.go = "exit";
				}
				else
				{
					if (sld.location == "LostShipsCityy_town")  
					{						
						string Str3 = npchar.location.locator;
						string Str4 = sld.location.locator;
						if (npchar.location == sld.location && strcut(Str3, 0, 5) == strcut(Str4, 0, 5))
						{
							dialog.text = LinkRandPhrase("��� �����, �� ���� �������. ��� ������������.", "��, ��� ��� �����, �� ���� �������!", "��� �� ���� �������, �������, ��� �� ��� �� ������"+ GetSexPhrase("","�") +" ��.");
						}
						else
						{
							dialog.text = LinkRandPhrase("� ����� �� ������ ������� " + npchar.quest.seekIdx.where + ".", "������� �������� �� " + npchar.quest.seekIdx.where + ". �� ���� ����������.", "��������� � ����, ������ ��� ��������� " + npchar.quest.seekIdx.where + ".");
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = LinkRandPhrase("��� ��� �����, " + npchar.quest.seekIdx.where + ". ������ ������������.", "��� ���� ��� �����, ����� ���!", "���� �� ��������? ��� �� ���-�� ����� �����.");
						}
						else
						{
							dialog.text = LinkRandPhrase("� ����� �� ������ ������� " + npchar.quest.seekIdx.where + ".", "������� �������� �� " + npchar.quest.seekIdx.where + ". �� ���� ���������� � ���.", "��������� � ����, ������ ��� ��������� " + npchar.quest.seekIdx.where + ".");
						}
					}
					link.l1 = RandPhraseSimple("���, �������. ������� ����, ��������.", "������� ����!");
					link.l1.go = "exit";
				}
			}
		break;
		//�������
		case "int_quests":
			dialog.text = "����������� ���� ������, "+ GetSexPhrase("�������","" + pchar.name + "") +".";
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "��, ��� ���� ����� ���������� � ������?";
				link.l1.go = "ansewer_1";
			}
			link.l10 = "��� ��������. ������, ��������...";
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = "������ � � ���� �� ����������. ��� ����� ������ �� ����.";
			link.l1 = "� ��� ���������, �������.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		//��������� ��� ���� ������
		case "InPrison":
			dialog.text = "��, "+ GetSexPhrase("��������","�������") +"! �� �������� ���?";	
			link.l1 = "��, � ��� � ���� ���� ������?";
			link.l1.go = "InPrison_1";
		break;
		case "InPrison_1":
			dialog.text = "������ ���� ����, ��� � ����� ��������!";
			link.l1 = "� ��� ���� ����?";
			link.l1.go = "InPrison_2";
		break;
		case "InPrison_2":
			dialog.text = "���� ������, "+ GetSexPhrase("����","�������") +". ��� ������� ������ '����� �����'. � ���� ����� ������ ������.";
			link.l1 = "������� �������������, ������.";
			link.l1.go = "InPrison_3";
		break;
		case "InPrison_3":
			dialog.text = "��� ����! ��, ��� ���, ��������?";
			link.l1 = "���� ����� ���� ����, �� ����������� ������.";
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "2");
			pchar.questTemp.LSCC.ElisHusband = "toElis";
			NextDiag.TempNode = "InPrison_wait";
		break;

		case "InPrison_wait":
			dialog.text = "��, "+ GetSexPhrase("����","�������") +", �� ���� ��� ��� ������� ����� ������. ����������, �������� ����� ����...";
			link.l1 = "�����.";
			link.l1.go = "exit";
		break;

		case "DontRemember":
			dialog.text = NPCStringReactionRepeat("��� ���� �����, "+ GetSexPhrase("�������","�������") +"?", 
				""+ GetSexPhrase("��������","�������") +", �� ��� ���-�� ������ ������?", 
				"������ �� �����, ��������� ���� � ��������.",
                ""+ GetSexPhrase("�������","�������") +", �� �� ��������� ���� ����������"+ GetSexPhrase("","�") +" ������. ����������, ����� �����...", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("���� ���� ����� �������� ���� ������. ������ ��� ���������, ��� �� ������� ������, ����� ���� �������?", 
				"���.",
                "�� ��...", 
				"�������� ���������.", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("DontRemember_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "DontRemember_1":
			dialog.text = "������ �� �����...";
			link.l1 = "���? ������ ������?";
			link.l1.go = "DontRemember_2";
		break;
		case "DontRemember_2":
			dialog.text = "������. � ��� � ������� ���������. �������, ��� � ����� � ���������� � ������ �� ������ ��������! ����...";
			link.l1 = "�-��, ���� ������ ����.";
			link.l1.go = "DontRemember_3";
		break;
		case "DontRemember_3":
			dialog.text = "����. �� ����� �� ����������!";
			link.l1 = "���, �� ����!";
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "6");
			pchar.questTemp.LSCC.ElisHusband = "toAdmiral";
		break;
	}
	NextDiag.PrevNode = NodeName;
}