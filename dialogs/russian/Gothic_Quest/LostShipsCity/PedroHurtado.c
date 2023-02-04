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
			if (npchar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					dialog.text = "���, ��� ��� �� �� ������ ���"+ GetSexPhrase("��","��") +"? �� ��� ��, �������! ����� �����������. ���� ����� " + GetFullName(npchar) + ", � ����?";
					link.l1 = "��� ��� - " + GetFullName(pchar) + ".";
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = "���, ��� ��� �� �� ���������� ����������? �������... �� ��� ��, ����� �����������. ���� ����� " + GetFullName(npchar) + ", � ����?";
					link.l1 = "��� ��� - " + GetFullName(pchar) + ".";
					link.l1.go = "FT_1";
				}
			}
			else
			{
				//����� ������������� � ��� ������� ��������			
				if (pchar.questTemp.LSCC != "AdmiralIsWaiting" && !CheckAttribute(npchar, "quest.store"))
				{
					dialog.text = ""+ GetSexPhrase("��������","�������") +", �� ������� ���������� ���� ������?";
					link.l1 = "������, ��� �� ������ �����.";
					link.l1.go = "StBegin_1";
					break;
				}
				// <-- ������ 
				dialog.text = "�� ���-�� �����"+ GetSexPhrase("","�") +"?";
				link.l1 = "������, � ��� ������ ��������. �� ������, ��� �� ������?";
				link.l1.go = "SeekCitizen";
				link.l2 = "���� ������ ���� ������.";
				link.l2.go = "int_quests";
				link.l3 = LinkRandPhrase("���-������ ���������� ��� ����������?", 
					"��� ������ � ������?", "��, � ������������� ��������"+ GetSexPhrase("","�") +" �� ��������� �������...");
				link.l3.go = "rumours_LSCC";
				if (CheckAttribute(npchar, "quest.store") && npchar.quest.store == "waiting" && npchar.chr_ai.type == LAI_TYPE_STAY)
				{
					link.l4 = "�� ���, � �����"+ GetSexPhrase("","�") +" ����� � ��� ����������� �����.";
					link.l4.go = "StStart_1";
				}
				//����� ������� �� ��������� ���
				if (pchar.questTemp.LSCC == "toSeekGoods")
				{
					link.l8 = "������, � ��� ��� ��������� ������.";
					link.l8.go = "SeekGoods";
				}
				//������ ������� �� ��������� ���
				if (pchar.questTemp.LSCC == "toSeekPeopleInCrew")
				{
					link.l8 = "������, � ������� �������, ����� ���� ������. ��������� ���� ����� �� ��� ��������.";
					link.l8.go = "SeekCrew";
				}
				link.l10 = "������...";
				link.l10.go = "exit";
			}
		break;

		case "FS_1":
			dialog.text = "����� �������. �� ����� �������� �� �������, ����� �� ����������. ����� ����� �������, ��� ��� ��������� �������"+ GetSexPhrase("����","���") +" ������ � ��� ����� � �������. � �����, ����� ���������� � �����!";
			link.l1 = "�������.";
			link.l1.go = "exit";
		break;
		case "FT_1":
			dialog.text = "����� �������. �� ��� ��, ���������� ����� ���������. ����� ��� ����� �������� ������, ��� ��� ����� ���������� � �����, ��� ����������...";
			link.l1 = "�������.";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//����������� �� � ��������
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("�� �� ���"+ GetSexPhrase("","����") +"!!! ��������� ������ ������!", "��� ��� ��! ���� � ����������, � �� ����� � ������ � �������! ��"+ GetSexPhrase("","�") +" �������"+ GetSexPhrase("","�") +" �����!", "�������! ������!!! ����� "+ GetSexPhrase("���","��") +", ��"+ GetSexPhrase("","�") +" �������"+ GetSexPhrase("","�") +" �����!");
			link.l1 = "�-���, ������!!!";
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = "��, ���, ������, ���?! �� �������� ������ ��������?! ������ �������� � ������� ������ ����, ��� ������ ������!";
			link.l1 = "��� ����!..";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//��������� �� ����������� ������
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("������, �� �� ����� ������. � �� ���������� �������...", "������, � ��� ��� �� ������� ��������� �����������. ����� ������.", "������, ��� ��, ��� ��� ���������, ������� ���, ������ ������? ����� ������, �� � ���� ��� "+ GetSexPhrase("���������� �������","�������") +"...");
			link.l1 = LinkRandPhrase("������.", "�����.", "��� �������...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "����������, �, ��� ��������� ����� ������, ����� ��� �� ������ � ��� � ���������� �������.", "������, �, ��� ��������� ����� ������, ����� ��� �� ������ � ��� � ���������� �������.");
				link.l1 = LinkRandPhrase("������.", "�����.", "��� �������...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "���������� �� ���������, "+ GetSexPhrase("��������","�������") +", ����� ������ � ������� � �����. � ���� ���� � ������������...", "��� �� ��������, ����� "+ GetSexPhrase("�������","������ ���") +" ����� ������ ���� � ������� �����������. ��� ���� ������...");
				link.l1 = RandPhraseSimple("�����"+ GetSexPhrase("","�") +".", "������.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
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
			dialog.text = "������ ����. ��������� ���, ��� ���� ������.";
			if (!CheckAttribute(NextDiag, NodeName+".l5"))
			{
				link.l5 = "������ �����! � ����� � ��� ����� ������?";
				link.l5.go = "ansewer_5";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l1"))
			{
				link.l1 = "��� ��� �� ������?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l2"))
			{
				link.l2 = "��� � ������ �������� ��������?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l3"))
			{
				link.l3 = "�� ��� ��� ���� �����?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l4"))
			{
				link.l4 = "�� ������� ����� � �� ���� ��� ������"+ GetSexPhrase("","�") +" �� ������� ��������������. ���, �������, �� ��� �����?";
				link.l4.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName+".l6") && pchar.questTemp.LSCC == "toSeekOldCitizen")
			{
				link.l6 = "������, �� ����� ��� ������ � ������?";
				link.l6.go = "ansewer_6";
			}
			link.l10 = "��� ��������. ������, ��������...";
			link.l10.go = "exit";
		break;
		case "ansewer_5":
			dialog.text = "���������, ���� ��... ������, ���� ���� ���������� � ��������� ����� ��������, ���� �� �� ��� ��� ����� �� ������"+ GetSexPhrase("","�") +".";
			link.l1 = "�������.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_1":
			dialog.text = "��� ����� ���������� ��������, "+ GetSexPhrase("��������","" + pchar.name + "") +". ��� ����� ��� ��, ��� ����� �������� ����� ���������������. ��� ������ � ��.";
			link.l1 = "��, ������ � �... ��������, � ������ ��� ����� ��������? ���� �����-������ ���������� ���� ���� ���������?";
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = "����� ����� �� �����. �������, ����� ��, �������� �� ����. �� � �� ���� �� ����� �������... �� ��� ���, �������. ����� ����� �� �����.";
			link.l1 = "� ����� ��� � �� ������� ������?";
			link.l1.go = "ansewer_1_2";
		break;
		case "ansewer_1_2":
			dialog.text = "��������, ���� ��. ������ ���� ��� ������ - ������ ����� ����������. ��� ��� � ���� �� ������� ����� ���������. ��� ���������, ��� ����� ������...";
			link.l1 = "�� ��, ����������� �����������...";
			link.l1.go = "ansewer_1_3";
		break;
		case "ansewer_1_3":
			dialog.text = "��� �� �����"+ GetSexPhrase("","�") +" ����, �� ������� � ���� ��� ���. ��� ���� ��� �����.";
			link.l1 = "�� ��� ��, �� ����� �������.";
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = "��-������, ���� ����� ��������� ������� � �������� ������, ���� ��� �� ���"+ GetSexPhrase("","�") +" � ����. �� � ����� ����� ���������� � ������� � �������. ��� ���� �������.";
			link.l1 = "�������...";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_3":
			dialog.text = "�� ��� ��, ��� � ��� - ����� ���������������"+ GetSexPhrase(", ��������","") +"...";
			link.l1 = "�������.";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_4":
			dialog.text = "�� ����... � ������, "+ GetSexPhrase("�������","" + pchar.name + "") +", ��� ������ � ���� �����, � �� ������ ���.";
			link.l1 = "��, ��� ������!";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_6":
			dialog.text = "���� �������, �� ������.";
			link.l1 = "����...";
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l6 = true;
		break;
		//����� ������������� � ������� ������� ��������
		case "StBegin_1":
			dialog.text = "���� ��� ���� �����, ��� ����� ����� �������...";
			link.l1 = "� ���?";
			link.l1.go = "StBegin_2";
		break;
		case "StBegin_2":
			dialog.text = "��������� ����� ���� � ������� ��. ����� ������� ����� �������.";
			link.l1 = "�, � ��������, �� ������. � ��� ��� �����?";
			link.l1.go = "StBegin_3";
		break;
		case "StBegin_3":
			dialog.text = "�� ������� '����������'. ��� ��� �������, ������ � ������ �������� �������. ���� �� ������ ���� ����, �� ������� ��������, ����� �����, �� �� ��������, � ����� ������� � �����.";
			link.l1 = "���� ��� �� ����� ������� ��������, � ����� ������� �� �������, �� ����� �� ����-�� ������? ���� �������� ����� �� �������.";
			link.l1.go = "StBegin_4";
		break;
		case "StBegin_4":
			dialog.text = "��, ��� �� ��� ��� ������. ���� ����� ���� �����������, ��� ��� � ���� ��������� �����. ��� ������ � ���� �� ����������, � ��� �� �������.";
			link.l1 = "���, ������ �������...";
			link.l1.go = "StBegin_5";
		break;
		case "StBegin_5":
			dialog.text = "�� ���, ������"+ GetSexPhrase("��","��") +"?";
			link.l1 = "�� ��� ��, ����� �����������. ����� ��������� ��� ������, ������ ��� �� ��������.";
			link.l1.go = "StBegin_6";
			link.l2 = "���, ��� ��� �����������. ���������, ������ ��...";
			link.l2.go = "StBegin_not";
		break;
		case "StBegin_not":
			dialog.text = "��, ��� ������, "+ GetSexPhrase("��������","�������") +"...";
			link.l1 = "���, �����.";
			link.l1.go = "exit";
			npchar.quest.store = "over";
		break;
		case "StBegin_6":
			dialog.text = "�������! ����, ����������� ����� �������. �� ������ ��� �� ����� �����, ��� ������ �����"+ GetSexPhrase("","�") +" - ��� � '����������', ���� � ���� ���� ��� ����� �� ����������� ����� � ������, ��� ������� ��������� �������. ��� � ����������, ��� � ����...";
			link.l1 = "������������.";
			link.l1.go = "exit";
			pchar.quest.LCS_SetPedroHurtado.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LCS_SetPedroHurtado.win_condition.l1.location = pchar.location;
			pchar.quest.LCS_SetPedroHurtado.function = "LCS_SetPedroHurtado";
			npchar.quest.store = "waiting";		
			AddQuestRecord("ISS_takeStoreMoney", "1");
		break;
		case "StStart_1":
			dialog.text = "�������! �� ��� ��, ����� � ��������?";
			link.l1 = "��, ��������.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LSCC_PedroRunOpenDoor");	
		break;
		case "StStart_Opened":
			dialog.text = "����� �������, �� ������ ���������.";
			link.l1 = "�������! ���-�� ��� ������ ������?";
			link.l1.go = "StStart_3";
		break;
		case "StStart_3":
		dialog.text = "� �� ������.";
		link.l1 = "������, ������.";
		link.l1.go = "exit";
		NextDiag.TempNode = "StResult";
		npchar.quest.store.money = pchar.money;
		AddQuestRecord("ISS_takeStoreMoney", "2");
		AddQuestUserData("ISS_takeStoreMoney", "sSex", GetSexPhrase("c�","���"));
			AddDialogExitQuestFunction("LSCC_PedroGoWaiting");	
		break;
		case "StResult":
			dialog.text = "�� ���, "+ GetSexPhrase("��������","�������") +", ���� �������, ��� � �������?";
			link.l1 = "��, ��� � �������, '��������"+ GetSexPhrase("'","a'") +" ��� ����� ����������.";
			link.l1.go = "StResult_1";
		break;
		case "StResult_1":
			dialog.text = "��, ����� � � �� ������. ��, ��� �� "+ GetSexPhrase("������� ����","������ ������� ������") +" - ����� � �����������... � ������ ����� ������ ������"+ GetSexPhrase(", �������","") +".";
			if (sti(pchar.money) <= sti(npchar.quest.store.money))
			{
				link.l1 = "������, ������ � ��� �� ���"+ GetSexPhrase("��","��") +". �� ���� ��� �����. ��� �������"+ GetSexPhrase("","�") +", � ����� �� ���"+ GetSexPhrase("��","��") +".";
				link.l1.go = "StResult_2";
			}
			else
			{
				npchar.quest.store.money = sti(pchar.money) - sti(npchar.quest.store.money); //������ �������
				link.l1 = "����� � ���"+ GetSexPhrase("��","��") +" ��� " + FindRussianMoneyString(sti(npchar.quest.store.money)) + ". ��������, ��� � ��������������, ����.";
				link.l1.go = "StResult_3";
			}
		break;
		case "StResult_2":
			dialog.text = "�� ��, ������ ������ � �� ������... ��, �� �����. ����� ����� - ��� �����, ������� ���-������ � ������ �����...";
			link.l1 = "���� �����.";
			link.l1.go = "StResult_4";
			AddQuestRecord("ISS_takeStoreMoney", "3");
			AddQuestUserData("ISS_takeStoreMoney", "sSex", GetSexPhrase("��","��"));
			CloseQuestHeader("ISS_takeStoreMoney");
		break;
		case "StResult_3":
			dialog.text = "��, ��� � �������! ���, ��� ��� ��� ������ �����������... ��, �����, "+ GetSexPhrase("��������","�������") +". ����� �������� - ���������.";
			link.l1 = "�������������.";
			link.l1.go = "StResult_4";
			AddMoneyToCharacter(pchar, -makeint(sti(npchar.quest.store.money)/2));
			AddQuestRecord("ISS_takeStoreMoney", "4");
			CloseQuestHeader("ISS_takeStoreMoney");
		break;
		case "StResult_4":
			npchar.quest.store = "over"; //���� ����� ����������	
			LAi_SetLoginTime(npchar, 6.0, 21.99);
			LAi_SetLSCoutType(npchar);
			LAi_group_MoveCharacter(npchar, "TmpEnemy");
			SaveCurrentNpcQuestDateParam(npchar, "location");
			NextDiag.TempNode = "First time";	
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//����� ������� �� ��������� ���
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat("��� �� ������?", 
				"�� ��� ���������"+ GetSexPhrase("","�") +" �� ����.", 
				"��� ���������"+ GetSexPhrase("","�") +"...",
                "�� ��� ��������� ���� �� ���� �������. ������ � �� ����!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("��� ����� ����, �����, ��������, ��������, ���������, �����, ������...", 
				"��... ������, �����������"+ GetSexPhrase("","�") +".",
                "�-�, �� ��.", 
				"�����"+ GetSexPhrase("","�") +", �����"+ GetSexPhrase("","�") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = "����� ��� ����?";
			link.l1 = "�� ���, �� ������ ������.";
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = "��, ����� � ������, �� � ������ ����������, ����� ������� � ������ ��������. ����� ����� �������. � ��� ����� � ������ - ��� ������ � ��������.";
			link.l1 = "����. �� ��� ��, ������� ����.";
			link.l1.go = "exit";
		break;
		//���� �������
		case "SeekCrew":
			dialog.text = "������!.. ���-�� ������ �� �����.";
			link.l1 = "� ��� ������.";
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = ""+ GetSexPhrase("�������","" + pchar.name + "") +", � ���� ���, ������������� ���� ��������� ���, �� ������� ����� ������� ������?";
			link.l1 = "��.";
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = "����� � ������ ������! � ��������.";
			link.l1 = "�������! ����� ������ ����������� �� '��� ��������', ��� ������� ���������� ���� �� ��� ��������� ���.";
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = "������, ������� ������ ������ �� ��������.";
			link.l1 = "�� ������������!";
			link.l1.go = "SeekCrew_all";
		break;
	}
	NextDiag.PrevNode = NodeName;
}