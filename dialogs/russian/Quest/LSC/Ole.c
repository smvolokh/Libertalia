// ��� ����������� - ����� �������
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "��� ��� ����?";
			link.l1 = "������.";
			NextDiag.TempNode = "First time";
		break;
		
		// � �������� - ������ �������
		case "store":
			dialog.text = "��... ����������, ��������. � ���� ���� ����� �������? ��� ����� �������...";
			link.l1 = "��. ������ ����. ��� ��... ���, ��� �� - ����� �������?";
			link.l1.go = "store_1";
		break;
		
		case "store_1":
			dialog.text = "�������! ����� ������� ��� ������ ��������! � ���� ���� ����� �������, ��������?";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "��. ������� � ���� ���, �� � ���� ���� ���� ��� ��� ���������. ��� �����, � ������ ��� �������. ��������?";
				link.l1.go = "store_2";
			}
			link.l2 = "��� � ���� ������� �������, �� �����, �� �������. � �� ������� � �� ������, ����� ���� ������. ����� �����...";
			link.l2.go = "pearl";
			sld = characterFromId("Axel");
			sld.quest.ole_pearl = "true";
		break;
		
		case "pearl":
			dialog.text = "�������! ����� �������! ��� ����� ������� - � �� ���� �������������. ������ ��������... ��� �������!";
			link.l1 = "���� ��! ��� ���� ��������! ����� ������� � ������� ���� ������� - ���� �� ������... ����� ��� ������� �����?";
			link.l1.go = "exit";
			NextDiag.TempNode = "pearl_repeat";
		break;
		
		case "pearl_repeat":
			dialog.text = "����� �������, ��������. ������� ��������... ����� �������!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "���, ����� ���� �������. �� �� �� �����, ���?";
				link.l1.go = "store_2";
			}
			link.l2 = "��, �� ��� �� ��� �� ��������� �����...";
			link.l2.go = "exit";
			NextDiag.TempNode = "pearl_repeat";
		break;
		
		case "store_2":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "��, ��! ��� ���! �������� ��� ����� �������! �������, �� ������ �������! ������ � ��� ���� ��� ���� �������. ����� � ����� ����...";
			link.l1 = "� ��� �� ����. ��, � ������ �� ����� ����������?";
			link.l1.go = "store_3";
			sld = characterFromId("Axel");
			DeleteAttribute(sld, "quest.ole_pearl");
		break;
		
		case "store_3":
			dialog.text = "�������, ������ �������. �� �� ������ �������, ��������? ����� �� ������ ��������. ��� ����� ��� �������� � �����. ��� ���� �����?";
			link.l1 = "���� ����� "+pchar.name+". ���, ��� ��� ���� ��������� ���� �������, ��� ��� ��� �����. ��� ���, �� ������, ��� �� ����� ���, � ��� ������� ������ ���.";
			link.l1.go = "store_4";
		break;
		
		case "store_4":
			dialog.text = "�������� ��� ��� ������� - �������� ������ �������. ��� ����� �������� ������ �����. ����� ���� ������ ����� - ������ ������ ��������. � ������ ����, �������. � ����� ��������!";
			link.l1 = "������ ������������! ��, ��� �� � ����� �����������, ���, ������ �� ��� ������: �� ������� �������� � ������� �����, � ��������� �������� ����� �� ������� ������? ��� �� ������, ��� �� ���� ���, ����� ��� ��� ����������.";
			link.l1.go = "store_5";
		break;
		
		case "store_5":
			dialog.text = "� ����� ����� ��������. ��� ������ �������. � ���� ���. � ����� ��� � ������. � ��� ������� � ���� ��� ������ ������� ��������, �� ����� � ����, �� ���� ����� ��������. ��� �� ����� ���, ���� �� ����� ���. � ����� � ��� ������� � ������, �� �� ���������. ������ ���������.";
			link.l1 = "�� ����� � ����? ���, �������, � ����, ��� ��� �� ����... �� � ��� �������� �����������. �����, ���, ��� ���� ������ ��������� ����� �������?";
			link.l1.go = "store_6";
		break;
		
		case "store_6":
			dialog.text = "��� ����� ���� �����. �� �����, ����� �����. �� ���� ��� ������, ����� ��� ����� ��� � �����.";
			link.l1 = "������ ����... �������, ��� �� ������ ��� �������.";
			link.l1.go = "store_7";
		break;
		
		case "store_7":
			dialog.text = "���, �� �������. ��� ������ ��� � ��� ����� � ��� ������ ��������� ����. � ������ � ������, ������ ��� �� ��� ������� ���� ���. ���� ���� �������� ����� � ����, �� � ������ �� �������� - ��-��-��... ������ ���� ������. ��� ����������� ���� ������, � ����. ������ ����\n� ������� - � ��� ����� ���� �����. ��� ���� ����� �����. � ���� ��� �������� ��� - � ��� ��� ������, � ��� ����� �����. ����� � ��� ��� �������� �� ���� - � ������ ����� � ����� ����, ����� ������, ���� �������� ���� ������ ���. ��� ��� ������ ������ ���� �������...";
			link.l1 = "�� ��� ��� ����������� � ���? ���, �������� ���� �������� ��� �������. �� �������, ���.";
			link.l1.go = "store_8";
		break;
		
		case "store_8":
			dialog.text = "���� ���� ������� ��� ��������, � �������: ���-�������... ��� �� ������� - ��� ����� ������� ��� ����� �������, ����� ���� �������� ���. �� ��� ����� ���� ��� �������?";
			link.l1 = "���... �������, ���, �� �� ������. �����, � ��� �� ��������� ������� �����... ���� ������, � ������? ���� ������� ������ ���, ��� ��� ������� ������ � �������� � ������ �� ���...";
			link.l1.go = "store_9";
		break;
		
		case "store_9":
			dialog.text = "������ �� ���. ��� �����. �� ��� ���������, � ���� ���� ������ ��� �� ��������� ������ ���� ������. ���� ������ �����, ��� ����� ������ �� ���. �� �� ��� ����� �������� ������. ��� ������ ������. ��� ������ ��������.";
			link.l1 = "���� ������? � ��� ���?";
			link.l1.go = "store_10";
		break;
		
		case "store_10":
			dialog.text = "���� ������ ����� ����� ���� ����� ��������. ��� ��� �����. �� ��� �����. �� ����� ������ �� ��� � ������ ���� ����� �������� ���������� �� ���. ���� ������ ������, �� ��� ��� ����� �������.";
			link.l1 = "��� �� ������� ������� ���� � ����? ��� ��� ���� ������ ������?";
			link.l1.go = "store_11";
		break;
		
		case "store_11":
			dialog.text = "��-��-��... ���� ������ ������� �� ������� ���, �� ��� ��� ����� ����� ����� � ����� ��������� �� �� ��������. ��� ������� � ������, � ��� ����� � ����������. � ���� ������� � ��������, ����� ������ ����� �������, � �������� ���� ������ ���������� �� ���. ���� ������ ��� ��� �������, � �� �����������.";
			link.l1 = "����� ���������... � ���� ���� ����������� � ����� ��������.";
			link.l1.go = "store_12";
		break;
		
		case "store_12":
			dialog.text = "�� ������ ���������� �� ��� � ����� � ������? ��� ���, � ������� ������� �������. ��� ����� ������� �������� ������. �� �� ������� ������? ��� ����� �������.";
			link.l1 = "���, � �� ����� ������. � ��� ���� ������, ��� ��� ������ ��� ���� ������.";
			link.l1.go = "store_13";
		break;
		
		case "store_13":
			dialog.text = "�, "+pchar.name+" ����� �������! ����� ���� ���� ���� � ���� ������� - �� ������ ���� ������ �� ��� � �� ��������� ���� ������ ������. � ������� ��� ��� ���� ����� ������� ��� ���. ������?";
			link.l1 = "�������, �����. ������ ������� ���� ����� ���� �������.";
			link.l1.go = "store_14";
		break;
		
		case "store_14":
			dialog.text = "� ����� ��� ������? �� ����� �� ������� � ������ '���-��������', � ����������. �� ���� ������ ������� ����� ���� �� �������.";
			link.l1 = "�� ����� �������� ��������� � ���-������ ����������. � ��������� ������: ��� ������ ���� �����? ���� � ���, ���, ��� � ��� ����� � ������ ����, ����� ������� ���.";
			link.l1.go = "store_15";
		break;
		
		case "store_15":
			dialog.text = "� ������� ���� ������ � ����� ������� �� ������� '��������'. �� ����� ������, � ��� ������ ���. ��� ������, ��� �� ����� ������, ������ ��� ������ ���������, � ��� �����, ��� �� ������. � ���� ���� ������ � ������ ��� ����. ������ ���� ����� ����� ���\n�� ��� ����� �����, � ��� ����� ���� �������� ���. �� ����� �� ����� ������, � �� ����� ������� ������ ������� ���� ������. ��� ���� ���� ������, � ���� ��� �������� ��� �� �������� � �������� �� ����� ���� ����� ��������. � ��� � ���� ��� ����, ������� �����. ����� ������� �����!";
			link.l1 = "������� �����? ��-��. ��� ����� ������ �� �������... ��� �� ������ - '��������'? � ������ �� ����...";
			link.l1.go = "store_16";
		break;
		
		case "store_16":
			dialog.text = "�������� "+pchar.name+", � �� ������ ��� ������ - �� ����� ������. �� ���� ������ �����, ����� ������ �������. ��� � ����� ���� �����, �� ���� ����� �� ���������. ��� ��� ��� ������. �� ���� �� ���� ���� ������, �� � ����� ����, ��� �������: ������� ��� ��� ���: ���-���... ���-���. � �� �������.";
			link.l1 = "� �������. �������, ���! �� ����� ��� �����! ����� � �� ����, ��� ���� �����������.";
			link.l1.go = "store_17";
		break;
		
		case "store_17":
			dialog.text = "������� ��� ��� ���� ����� �������. ����� �������, �������.";
			link.l1 = "��, ��! ����� �������! ������. ��� ��������, ���!";
			link.l1.go = "store_18";
		break;
		
		case "store_18":
			DialogExit();
			LAi_SetLoginTime(npchar, 12.0, 21.99);
			LAi_SetCitizenType(npchar);
			LAi_group_MoveCharacter(npchar, "LSC_CITIZEN");
			sld = characterFromId("Nathaniel");
			sld.dialog.currentnode = "diffindoor";
			sld.greeting = "Nathaniel_ill"; // ���� � ������� ������
			pchar.questTemp.LSC.DiffIndoor = "true"; //������� ������� � ������
			pchar.questTemp.LSC = "mechanic"; // ���� �� �������� � ���������
			NextDiag.CurrentNode = "ole";
			AddQuestRecord("LSC", "6");
		break;
		
		case "ole":
			dialog.text = "�, ���� "+pchar.name+"! ��� ��� ������! ��� ����?";
			link.l1 = "�������, ���, ��� ������. � ���� ��� ������� � �����.";
			link.l1.go = "exit";
			link.l2 = "��������, ���, �� �������, ��� ������ �������� ��������� ����� � ����, �� �� ������ �� ����������... �� � ������� ��� ��� �� ������, � �� �������, ��� ��������� �� ��� ��� ��� ���� ������. ��� ���� ��� ��� �������?";
			link.l2.go = "lock";
			NextDiag.TempNode = "ole";
		break;
		
		case "lock":
			dialog.text = "� ��� ���� ����� ������� ��������. ��� �������� �� ���� ������ �� �������� � ������. ���� ���, �� �� ����. ��������� ������� ������, �� ����������� - �����. ��� ����� �� � ����� ����� ����-������� ������. �� ������ ����� ����� � ����� � ������ ��������. �� ������ ����� � �����. � ��� �� ������ � ����� ������� � �������� ������� ��� ���� ��������.";
			link.l1 = "�������. ���, � �� �� ������ ������� ��� ��� �������? � �� ��������...";
			link.l1.go = "lock_1";
		break;
		
		case "lock_1":
			dialog.text = "������, ���� "+pchar.name+", � ������ ���� ��� �������. ������ ���� ���� �������, ������� ��������� ����� � �������� ��������. ��� ����� ������� ��� � ���� ��� ��� ���� ������. ��� ����� � �������� ��� ������ ������� � ����.";
			link.l1 = "������� �� �� ��� ������?";
			link.l1.go = "lock_2";
		break;
		
		case "lock_2":
			dialog.text = "����� �������, ���� "+pchar.name+", � � ���� ���� ������� �������?";
			link.l1 = "��, ����. �� �� �� �����, �� �� ������� �����. �� � ����� ���� � �������, � ����� ������� ���� �� ���� ������� �� ����� �������.";
			link.l1.go = "lock_3";
		break;
		
		case "lock_3":
			dialog.text = "�� ����� �������? ��, ��� ������! ����� ��� ���: �������� ���, ��� ����� ��������� �� ������� �������, �� �������� ���� ������ � ��������� ������� � �����, ���� ��� �� �������. � ���� ��������, � ���� ������ � ������ ����... � ��� ��� ���� ����� �������. � � ����� ���� �������.";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l1 = "�������! ��� ���� ����� �������. �����.";
				link.l1.go = "lock_4";
			}
			link.l2 = "������ � ������ ����? ���! ���������� ������. ������, ���, ������������. � ������� ���� ���� ������� � ��� ��������.";
			link.l2.go = "exit";
			NextDiag.TempNode = "ole_1";
		break;
		
		case "ole_1":
			dialog.text = "�, ���� "+pchar.name+"! ��� ���� ������! ��� ����?";
			link.l1 = "�������, ���, ��� ������. � ���� ��� ������� � �����.";
			link.l1.go = "exit";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l2 = "� ������ ���� ���� ����� ������� �� �������.";
				link.l2.go = "lock_4";
			}
			NextDiag.TempNode = "ole_1";
		break;
		
		case "lock_4":
			RemoveItems(pchar, "jewelry52", 5);
			PlaySound("interface\important_item.wav");
			dialog.text = "�������! ����� �������! �������� "+pchar.name+" ��� ��� �������! ����� � ����� ����, �������!.. ���� "+pchar.name+", �� ��������, ��� �������� ���� �� ���� �������, ����� ���������?";
			link.l1 = "������, ���. � ��� ������� �� �� ������� ����. � ������ ���� � �����.";
			link.l1.go = "lock_5";
		break;
		
		case "lock_5":
			GiveItem2Character(pchar, "keys_skel");
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			dialog.text = "�������, �������, ������ ���� "+pchar.name+"! ��� ���� �������. ������������ ��� ������: ���������� �� ������� � ������� - �����-������ �� � �������. ���� �� ������ �� ���� - ������, ����� ����� ������ � ����������� ����� ���� ������ �� ����.";
			link.l1 = "�������. �����, ��� ���������, ��� � ����.";
			link.l1.go = "lock_6";
		break;
		
		case "lock_6":
			dialog.text = "�������, ���� "+pchar.name+"! � ���� ���� ���� ����, ��������-�������� � ����� �������. ���� ���� ����� ����� �� ������. ��� �� ��������� - �� ����, � �� ����� ������ ������� ��� �����. �� ����� �� �������? ��������, ����� �������� ������! �� ����� ������ �� �����.";
			link.l1 = "������... ��, ���� ����������. �� ����� ���� �� �����, ���� �� ������, �� ������ �� �����?";
			link.l1.go = "lock_7";
		break;
		
		case "lock_7":
			dialog.text = "���� "+pchar.name+", �� ����� ��������. ����� ����? ���� ���� ����, ������, ���� �����. ���� ���� ����� - ������ ���� ����. ��� �� ������. ��� ����. ������, ���� � �����. ���� � ����� �� �������, ������, � ����� ���� �� �������. ����� � ���� �� �����. � ��� �����? ��� ������� ����, ������ ������� �������� ������ ���-�� ������. ��� �����.";
			link.l1 = "������� �����, �� ���� ���������. ������, � ����� � ���� � ���� ������. �� ������ �� ���� �������, ��?";
			link.l1.go = "lock_8";
		break;
		
		case "lock_8":
			dialog.text = "��, ��� ����� ���� ����� �������. �� ���� ��� ��, ���� "+pchar.name+"?";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l1 = "���, ������ ���� �������.";
				link.l1.go = "key";
			}
			link.l2 = "� ���� ���� �� ���, �� � ����������� �������.";
			link.l2.go = "exit";
			NextDiag.TempNode = "ole_2";
		break;
		
		case "key":
			RemoveItems(pchar, "jewelry52", 5);
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "sant_anna_key");
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "�������! ����� ������� ��� ������ ��������! ��� ��� �������! ���, ���� "+pchar.name+", ������ ������. � ����� �� �������, ��� �����. �� �������, �� ���� �� ������� �������� ������.";
			link.l1 = "��, �� ����� ����, ���! ������� �� ����. ��� ��������!";
			link.l1.go = "exit";
			NextDiag.TempNode = "ole_3";
		break;
		
		case "ole_2":
			dialog.text = "�, ���� "+pchar.name+"! ��� ���� ������! ��� ����?";
			link.l1 = "�������, ���, ��� ������. � ���� ��� ���� ������.";
			link.l1.go = "exit";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l2 = "� ������ ���� ���� ����� ������� �� ���� ����.";
				link.l2.go = "key";
			}
			NextDiag.TempNode = "ole_2";
		break;
		
		case "ole_3":
			dialog.text = "�, ���� "+pchar.name+"! ��� ���� ������! ��� ����?";
			link.l1 = "�������, ���, ��� ������. � ���� ��� ������� � �����.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ole_3";
		break;
		
		case "return":
			dialog.text = "��, ���� "+pchar.name+", �� ��������! �� �������� �� ������� �������! �� �������� ���� � ����? ���� "+pchar.name+", �� ������, �������?";
			link.l1 = "�������, �����, ���. ����� ���������� �� ����! �����, ��� ���� ��������� ������ ���, ��-��!";
			link.l1.go = "return_1";
			link.l2 = "�� ��? � ����� ����� ����? � ���-�� ����� �������� �� ��������...";
			link.l2.go = "return_3";
		break;
		
		case "return_1":
			dialog.text = "�������, ��������! ��� ����� �������� ����, ��� �������! ��, �����, � ����� ����� �������? ���, � �������!";
			link.l1 = "������ �� �������, ���, � �������� ������� ����. � ��� �� ���������...";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LSC_SetOlePassenger", 10.0);
		break;
		
		case "return_3":
			dialog.text = "�� ������, �� ������! �� ������ ������� ���! ������ ������! ������� ���! ������ ������!";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload45", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "authority", -3);
			if (GetCharacterIndex("Mary") != -1) // ����
			{
				sld = characterFromId("Mary");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else // ����� ����������
			{
				chrDisableReloadToLocation = false;
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			}
		break;
		
		// ������� ���
		case "givemepearl":
			dialog.text = "��������, ��������... ��� ����� ��� ���� ����� �������. �� ����������, ��� ��� ����� �������!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "� ����, ��� �� ������ �� �������. ���, ����� ���� �������. �� �������?";
				link.l1.go = "givemepearl_yes";
			}
			link.l2 = "��, �� ��� �� ��� �� ��������� �����... ��� � ���� ������ �������, ���, ����!";
			link.l2.go = "givemepearl_no";
			DeleteAttribute(npchar, "pearl_date");
		break;
		
		case "givemepearl_yes":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			dialog.text = "�������! ������, ������ ���� "+pchar.name+"! � ��� ���� ��� ���� �������, �������� ������ �������! � ����� ����� ����� � ����...";
			link.l1 = "��, � � ���� �� �� ����� ��������?..";
			link.l1.go = "givemepearl_yes_1";
		break;
		
		case "givemepearl_yes_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			SaveCurrentNpcQuestDateParam(npchar, "pearl_date");
			npchar.quest.pearlqty = sti(npchar.quest.pearlqty)+1;
			NextDiag.CurrentNode = "givemepearl_repeat";
		break;
		
		case "givemepearl_repeat":
			dialog.text = "������� �� �������, ������ ���� "+pchar.name+"!";
			link.l1 = "�� �� �� ���...";
			link.l1.go = "exit";
			NextDiag.TempNode = "givemepearl_repeat";
		break;
		
		case "givemepearl_no":
			dialog.text = "��� �������? �� ��� �� ���, ���� "+pchar.name+"?! ��� ����� ��� ������ ������� �������... � ������ �� �������. ��� ���, ����� � ����� �� �����. ���� ������ �������...";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "�� � ���� �� �� �������? ��� �� ������ ���� ������? ���, �� ������ � ���� �� ����. ������, ����� � ��������... ���! ��, ������ ���� ����� ������� � ���������. �� �������?";
				link.l1.go = "givemepearl_yes";
			}
			link.l2 = "���� �����, ���. ������� ������� �� ���� - ������ ����, � ���� �� �����. �� � ����� ��� � �������������� - ���� ���� �� �������. ���� ���� �� ����� ������, �� �����...";
			link.l2.go = "givemepearl_no_1";
		break;
		
		case "givemepearl_no_1":
			dialog.text = "��������, ���� "+pchar.name+". ��� ����� ����� �������, ����� �� ������� �� �������� � ����...";
			link.l1 = "��, � ����� ��� ����, �� ��� � ����� ��������? ������, ���. �����.";
			link.l1.go = "givemepearl_exit";
		break;
		
		case "givemepearl_exit": // ��� ������ - ����� �� ������ �� �����
			DialogExit();
			RemovePassenger(Pchar, npchar);
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			DeleteAttribute(pchar, "GenQuest.Ole");
		break;
		
		case "mother":
			dialog.text = "���� "+pchar.name+"! ��� ����� ��� ���� ����� �������. ���������... �� ����������, ��� ��� ����� �������!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "� ����, ��� �� ������ �� �������. ���, ����� ���� �������. �� �������?";
				link.l1.go = "mother_1";
			}
			link.l2 = "��, �� ��� �� ��� �� ��������� �����... ��� � ���� ������ �������, ���, ����!";
			link.l2.go = "givemepearl_no_1";
		break;
		
		case "mother_1":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "�������, �������, ������ ���� "+pchar.name+"! ������ � ��� ���� ��� �������. ��, ���! ������ ��� ����� ������� �� ����, � ���� �� ������� ���...";
			link.l1 = "��������, � ����� ���� �� ��� ����� ��������? � ������� �������, ����� ���� ��� ���������... ����, ����� �������? � ��� ������ - �� �� ������?";
			link.l1.go = "mother_2";
		break;
		
		case "mother_2":
			dialog.text = "������ ���� "+pchar.name+" ����� ������� ��� ������� ��� ��� ����... ��� ��� ���������, ����� ������ ������ �������� �� ����� �������. ��� ��� ����������� � ����� � ����. ���� ����� ������������ �� ���, � ��� �� ����� ��������� �����, ���� �� ������� ��� ���������� �������\n� �����, ������� �� ���� - ���� ��� �� ������ �������. ������ ��� ������ �� ���. ���� "+pchar.name+", �������� ���� �����, ����������! � ���� ���������� ��� ����, ������ �� �� �������. ��������!";
			link.l1 = "�������, ��� �� ������ �������... �� ���� ����� �� ������ ��� ��������. ���� ���, ���� ������� �� ���� �� ��������� ��������� ��������? � �� ��� ��� ���� ������� ���� �������? ���� �����-��...";
			link.l1.go = "mother_3";
		break;
		
		case "mother_3":
			dialog.text = "������ ���� � ����, ������ ���� "+pchar.name+". � ��� ���� �� �������. ��� ����������, ����� ������ �������.";
			link.l1 = "� �� �����, �� ��� �� ���� ���, �� ������? ��� ����� ���� ����?";
			link.l1.go = "mother_4";
		break;
		
		case "mother_4":
			dialog.text = "��� ����� �� �������, � ������, � ������ � ������� ������.";
			link.l1 = "��� ������! �� �� ������, ������� ��� ��������, � ������� �� ��� ������� � �������� �������? ��� ���������� ���� ������? ��, ��� ������� �����, ��� ��...";
			link.l1.go = "mother_5";
		break;
		
		case "mother_5":
			dialog.text = "� �� ����, ��� ���������� ������. ���� - ��� ������, ���� �������� ���� - �� �� �������! � �� ���� � ������ � ������� ������. �������� �����, �������. ������ ���� � ����, ���� "+pchar.name+". �� ����������...";
			link.l1 = "��, �����. ����� �� ������ ������� ������ � ������ ���� � �������� ������� � ���������� ���� ����. ��� �� ����� ����?";
			link.l1.go = "mother_6";
		break;
		
		case "mother_6":
			dialog.text = "����? �� ��������, ���� "+pchar.name+". ���� ����� �����. � � ���� ���� ��-������� �����?";
			link.l1 = "� �������, ����� ��� ��������... ������, ���, �� ��������� ����� ���� ���. � ������ ������ �� �������.";
			link.l1.go = "mother_7";
		break;
		
		case "mother_7":
			dialog.text = "�������, �������� "+pchar.name+". �� �����, ����� ������ � �������! ����� ��� ������ ����!";
			link.l1 = "��...";
			link.l1.go = "mother_8";
		break;
		
		case "mother_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			DeleteAttribute(npchar, "pearl_date");
			// ������ ����� ����������� � ��������� �� ��� � ������
			LocatorReloadEnterDisable("Marigo_town", "houseSp2", false);
			sld = GetCharacter(NPC_GenerateCharacter("Agnes", "women_18", "woman", "towngirl", 10, HOLLAND, -1, true, "quest"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "�����";
			sld.lastname = "�����������";
			sld.dialog.FileName = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "agnes";
			//sld.greeting = "";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Marigo_houseSp2", "barmen", "stay");
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
		break;
		
		case "home":
			dialog.text = "����... ����, �������! � ��������!";
			link.l1 = "�����...";
			link.l1.go = "home_1";
		break;
		
		case "home_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			bDisableCharacterMenu = true;//������� ����������
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
			DoQuestFunctionDelay("LSC_OleReturnHome", 18.0);
		break;
		
		case "home_2":
			dialog.text = "�������, � ������ ���� ����� �������! � ������ �� ���. ������ � ���� ����� ����� �������� ��������. �� ������ �� ��������� �� ����?";
			link.l1 = "�������... (������) ���! �����, �����? ������ �� ����? �� ���� ��� �������, ��� ���������!";
			link.l1.go = "home_3";
		break;
		
		case "home_3":
			sld = characterFromId("Blaze");
			dialog.text = "�������, ������... ���. � ��� ����� �� �������. ��� �������� ������ ��������, �������� ���� "+sld.name+". �� ���� ���� �� ���� ������� �������, ����� ������� ������� � ������ ���� �����...";
			link.l1 = "���... �� ��� �����, �� ��� ����� ������� ��������... ��� � ���� ������, �����! ������, ������ ���� ����������, �� �� ��������� ��������! ������ � ���� ������ �� ������, �������! �� ����� ���� � ����� ������, � ���� � ���� ����������... � ������� ���� ����, ������!..";
			link.l1.go = "home_4";
		break;
		
		case "home_4":
			dialog.text = "�������, � ��� ������ �� ����... � ���� �������� � �����. �� ������ �� ���������? ������ �� �������?";
			link.l1 = "(������) ���, ���... ������, ������ ����, �����!..";
			link.l1.go = "home_5";
		break;
		
		case "home_5": // ������������ pchar
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Agnes");
			sld.dialog.currentnode = "agnes_11";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "final":
			dialog.text = "���� "+pchar.name+"! ��� ������, ��� �� �����! �������, ��� �������� ���� � ���� �������. ��� ��� ������ �����, ������ � ���... ���� ��� ������� - ����� �� ����, ������, ���� "+pchar.name+"?";
			link.l1 = "��, ���. ��� �������. � ���, ��� �� ��������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "final";
		break;
		
//----------------------------------------- ����������� ������� -----------------------------------------------
		//��������� �� ����������� ������
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("������, �� �� ����� ������. � �� ���������� �������...", "������, � ��� ��� �� ������� ��������� �����������. ����� ������.", "������, ��� ��, ��� �'��������, ������� ���, ������ ������? ����� ������, �� � ���� ��� ���������� �������...");
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
				dialog.text = NPCharSexPhrase(NPChar, "��������� �� ���������, ��������, ����� ������ � ������� � �����. � ���� ���� � ������������...", "��� �� ��������, ����� ������� ����� ������ ���� � ������� �� ���������. ��� ���� ������...");
				link.l1 = RandPhraseSimple("�����.", "������.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- ����������� �������
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}