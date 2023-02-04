// ������ ��� ����� - �������� ���� �����
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if(pchar.questTemp.Saga == "helena1")
			{
				dialog.text = "��, �������! �� ������, � ��� ���������� �����. �� �� �������������, ����� ������ ���� � ���� ����!";
				link.l1 = "�� ��� ��������� �������, ������ ��� �����. ������� ������ ����� ������, ����� �� ��� �� ����. � � ������ � ��� �� ���� ���������� �����.";
				link.l1.go = "Helena_hire";
			}
			else
			{
			dialog.text = "������������, "+pchar.name+"! ����� ���� ��� ������! �� ������� �� ������� ����?";
			link.l1 = "�������, ������ ��� �����, �� ���� ���� ����.";
			link.l1.go = "exit";			
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "FindHelena":
			dialog.text = "��� ��� ������, ���?";
			link.l1 = "�� - ������ ��� �����?";
			link.l1.go = "FindHelena_1";
		break;
		
		case "FindHelena_1":
			dialog.text = "������ ���. � ��� ��� � ���-�� �� ��������, ������� �������. ��� ��� ���������, ��� �� �� ���� ������?";
			link.l1 = "���� �������������� ������� ������� ����� ������, ������ ��� �����. ������ �� ������, ��� ��� �������? � ������, � ����� ���� ������� �������...";
			link.l1.go = "FindHelena_2";
		break;
		
		case "FindHelena_2":
			dialog.text = "��, � ��������� ������� � ����! ��� ����������: ���� ���� ����� ���� ��������� ������ ����. ����� ����� ������ ���� � ����������� ��������� �� � ���� ���� �����. ��� � ���������� ��������� �� ���� ���� ������� ���� �������� ������ � ����� �������� � ������������� ��� �������� �������\n������� ������� � ����������� ������ ����������� ��� ��������, � ������� �� ������� �� �� �������. �������� ������� ��� ����� �������. ������ ��������� � ��� �� ����. � ��� ��� ����� � �� ����� ����� �� �����.";
			link.l1 = "���� �����, �� ��� ������ ������?";
			link.l1.go = "FindHelena_3";
		break;
		
		case "FindHelena_3":
			dialog.text = "��� �� �������� �������������! ��, ��������, ������, ��� �������� ������� � ���� �� ���� ��������� �������, � ������ � ����� ���������� ��������. ��� ��� ������ �� ���� ����� �� ������� ��� ���������. ����� ��� ���-�� �� ��������...";
			link.l1 = "� �������? ����� �� ��� ������������ �� ��������� �������?";
			link.l1.go = "FindHelena_4";
		break;
		
		case "FindHelena_4":
			dialog.text = "� ����� ���������� � ��������, �� �������, ��� ������� ������� � ���������� ������� ��������� ����������, � ������ ��������, ���� ������� ������ �� � ����� ������ ��������� ������� ����������� ������� ��� ���. ������� ��� ��� ������ �����. � ���� �� ������� ��������� ������ ��� ������ ���������\n��������� �� ������� � ��������� �������� �� ����� ����������� ���������� ��� �����, ��� ��� ����� ���������������� � �� ����� ������ ��� �� ����������. ''������'' ��������� ��� ��� ����������� ������, � ��� ������ � ����� ���� ��������� �������, ������� �������� ��������.";
			link.l1 = "��������, ��������� �� �� �������� ��������� �����-������ �������, ��� ��������� ���-�� ��������, ���� �� ����� �� ������� ��������?";
			link.l1.go = "FindHelena_5";
		break;
		
		case "FindHelena_5":
			dialog.text = "��, �� ��� ��! ��, ����� ������� ������, ����� ����� ����������� ������. ����� ���... ���� ������ ����� ����� �������� ������� �� ���������� ������� � �������� � ��������. ��� � ���� ������� ������, ���� � ���������\n��� ��� ������� � ��� ���� ��������. ��� ������ �� ��� �� ����� � ��� ����� ��� �� ���������. �������� ������ ������ ������ ����������. ��� � ���� ����, ����� �� ���������!";
			link.l1 = "����� �� ���, ������ ��� �����, ������ ����������, ��� �� �����-�� ���� �����������...";
			link.l1.go = "FindHelena_6";
		break;
		
		case "FindHelena_6":
			dialog.text = "���? �, �� ��������� ��������, � ���� �� ���� �� ����. � ��� ��� �? ��, ��, �������. ��� ��� ������� ��� ������� ������ �������. �� �� ����� ��������, ����� � �������-��-��� ���������� ������, �� ���������� ����� ���������. ������� ���� ��������� �����, �� �������� ������� ������-�� ��� �������������.";
			link.l1 = "� ��� �� �����?";
			link.l1.go = "FindHelena_7";
		break;
		
		case "FindHelena_7":
			dialog.text = "�� � �������� �� ���. �� �� ���� �� ����� ������ ����������� ������� ����������� �������, ��� ��� ���� ��� ��������. � ��� ������� ������ � ���������� ������... ��� ��, � ����� ���� ��� ������ ����� ����� ����������!";
			link.l1 = "� ��� ����� ���� ����������� ��������?";
			link.l1.go = "FindHelena_8";
		break;
		
		case "FindHelena_8":
			dialog.text = "��, �� ������ � ��� �����! ��������� ����������� � ��� ������ �����. ��������, � ��� ��� �� ���������. �� �������� � ����� ��������. �� ������ �������. ������ ����� ��� ��������� �������� ��������� � ��� ��������� ��-�� �����. ��� ������ ��� ��������. �� ��� ��� �������� �������� �� ��������� ���� �� �������� �����.";
			link.l1 = "��� �, ������� �� �������. �������� �������� ���� �������. ���� ���-������ �����, ����������� ������ ��� ��� ������� ��������. ������� �������� ���� ���� ����� � ��������.";
			link.l1.go = "FindHelena_9";
		break;
		
		case "FindHelena_9":
			dialog.text = "�� ����������� ����������� �� ������? �� ����������� ��� ������� �� ������ ����, �� �������� �� ��� �� ������� ����, �� ������� �� ���� ����! � ���� �������� �� ���! ������� ���� ���, ����������� �������?";
			link.l1 = ""+pchar.name+". "+GetFullName(pchar)+". ������� ��������� ������ � ������� �������, ������ ��� �����. �� �������!";
			link.l1.go = "FindHelena_10";
		break;
		
		case "FindHelena_10":
			DialogExit();
			NextDiag.CurrentNode = "FindHelena_wait";
			AddQuestRecord("Saga", "1");
			pchar.questTemp.Saga = "maruntown";//���� � ��������
			SetFunctionTimerCondition("Gladis_SetHome", 0, 0, 1, false);
			int iTime = 25-MOD_SKILL_ENEMY_RATE;
			SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime, false);
		break;
		
		case "FindHelena_wait":
			dialog.text = "�� ���-������ ������ � ���� ������ �����, "+pchar.name+"?";
			link.l1 = "�������, ������ ��� �����, ���� ������ ������, �� ����������� ����. � ��������� ������. ���������� ������ ��������  ���� �� ���� �������� ������� ��������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FindHelena_wait";
		break;
		
		case "Helena_die":
			dialog.text = "�� ��������, �������. ���� ���� ������ ������� ����� �� ����� �� ������ �������. ����, ��� ��� ��� ���������� ����� �������! �� �������� � ���� ���������...";
			link.l1 = "������� ��� ��������������. ��� ������ ���������...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_exit":
			dialog.text = "��, ������� �������, �������� ���� ������� � ���� �����...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_regard":
			dialog.text = "�� ����, ��� ������������� ���, �������, �� �������� ���� ������. ��� ��� ���������� ���, � � ���������� ����� ��������� � �������������. ���, �������� ������� ��������. ��� �������, �� � ��������� �� �� ����� ������. � �� ������ ������������!";
			link.l1 = "������, ������, �� ����. �� � ������ ���� ���� ����� �� ��-�� �����, � �� ��� ������.";
			link.l1.go = "Gladis_regard_1";
			link.l2 = "�������� ��� ������ ����, ������. ��� ��� ������.";
			link.l2.go = "Gladis_regard_2";
			sld = characterFromId("Helena");
			LAi_SetStayType(sld);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			// ������� �����
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);
		break;
		
		case "Gladis_regard_1":
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "� ����� ����, ��� ������ ���� ���-�� ��������� �� ��� ����������� ��������. ����� ����� ���� ������ ������� ��� ���, � �� � ������ ����� ���� ������ ��� ����� � ����� ����� ��� � ����.";
			link.l1 = "�������, ������ ��� �����. � ���� �������� ��� � ����� �� �����������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_regard_2":
			dialog.text = "��, �� ��� ��... � ������ ������, ����� ��� ����������� �������� ��� ���� �������� ������������. ������, ��� ����� ����� ���� ������ ������� ��� ���, � �� � ����� ����� ���� ������ ��� ����� � ����� ����� ��� � ����.";
			link.l1 = "�������, ������ ��� �����. � ���� �������� ��� � ����� �� �����������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
			pchar.questTemp.Saga.Helena_friend = "true";//������� ��������� ����� � �������
		break;
		
		case "Gladis_wait":
			dialog.text = "��, �����! ������ ���� ������ � ���� � ���� ��������� ���� ������. �� ������ ������ �����? ��� � ���� � �������, �������. ����� ������ ''������'' � ������ ��������� ��������, ��� ����� �� ������� �� �����. � ������� ���� �� � ����� ��������...";
			link.l1 = "��������� ���, ������ ��� �����.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_history":
			dialog.text = "��, �����! ������ ���� ������ � ���� � ���� ��������� ���� ������. �� ������ ������ �����?";
			link.l1 = "���. � ���� ������ ��� ��������� �������� � ����� ����������� �� ���� �������������. �� ��� � ������ ������� ������� ������������ �����. ��� ������ ���� ��������?";
			link.l1.go = "Gladis_history_1";
		break;
		
		case "Gladis_history_1":
			RemoveItems(pchar, "bucher_ring", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "���� ����������! ��� ��������...  �� ����!";
			link.l1 = "������� ��� ������?";
			link.l1.go = "Gladis_history_2";
		break;
		
		case "Gladis_history_2":
			dialog.text = "���. ����� ���� �������� ����, ���� � ������ �� ����� �� ����. �� �������� �������, � � ������ ������ �� �� ������ �������. ��� �������� �����, �� ��� ��, ��� ��� �� ��� ����, �� ���� ���� ��.";
			link.l1 = "��� ��� �� ��������� �������� �������?";
			link.l1.go = "Gladis_history_3";
		break;
		
		case "Gladis_history_3":
			dialog.text = "�� ���� �������� ��� ��� ����� �����, ������� ������� '������'. � ������ ��� ����� ���� ���. � ���� � �������� ������� ������� � ������ �������� � ������� ������. ������ ������ �� ���� ������� ��� ���, ����� ����, ��� ��� ���� ������ �������\n� �� �� �� ��� �� �������� ����� ������� � ����� �����. ��� ��� ���������� �������. � ��������� ����� � ����� ���� �������� ������ ����� �������� ���. ��� ������� �����? �� ���?";
			link.l1 = "�����������, ������ ������! ��� ������� ��������� ��������, ��� ����� ������� �� �������, ���� �� - ��� ������ �������, ���� ��� ������ � ������. ������� � ���������� � ���, ��� ������ ��� �������� ��� ���� ��������...";
			link.l1.go = "Gladis_history_4";
		break;
		
		case "Gladis_history_4":
			dialog.text = "";
			link.l1 = "������ ����������� �������� ��� ������� ��� ������� � ��� ����� �� ������� ��-�� ����, ��� �� ���� ��������� ��������� ������ ������ ��������. �� ���� �� ����, �... �������, �������� � ��������. �������,  ������, ������� ���� ����� ������ �� �������� ������� �� ������ � ����? ����� ����, �����-�� ����������?";
			link.l1.go = "Gladis_history_5";
		break;
		
		case "Gladis_history_5":
			dialog.text = "��� �������� �������� ������ ������ �����. ��������, ��� ��� �� ����������. ����� ����� ���� ������ �� ������� ����������? � �������, ��� ��� ���� ��������� �����. ��� ���� ����� ���������� � ������� �� � ����. �� � �� ������ ������ ��������� ����, � ���������� �������, '�������'\n���� �� ���... ���� ������, � ����� ��� ���, ���� �� ���������� ��� �����-������ ���������, ��� ��� ��� ������.";
			link.l1 = "����������, ������ ��� �����. � ������ ���� ������� ����� �� �����. ��� ����� ����� �������������� � �������� ���������.";
			link.l1.go = "Gladis_history_6";
		break;
		
		case "Gladis_history_6":
			GiveItem2Character(pchar, "map_half_beatriss"); //��������� �����
			PlaySound("interface\important_item.wav");
			dialog.text = "�� ����� ��������� ���, �����! � � ��� ������ �� ����, ��� ��� �����������. �������� ���� �� ���� �������� ����. �� ����� �������� �� � �������, ��� ��� ������ ����. �� ��� ����� �������� ��� ���� - ��� ����� ���� ������ ��������� ���������� � ����� �����! ������, ������!";
			link.l1 = "�������, ������. �������� ������������� ������������. ��������� � ��������� �����������.";
			link.l1.go = "Gladis_history_7";
			if (CheckCharacterItem(pchar, "chest"))
			{
				link.l2 = "����� ���� ������� ��� �������� �����. � ���� ���������� ������.";
				link.l2.go = "Gladis_history_8_1";
			}
		break;
		
		case "Gladis_history_7":
			DialogExit();
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol5");
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			AddQuestRecord("Saga", "22");
			AddCharacterExpToSkill(pchar, "Leadership", 50);
		break;
		
		case "Gladis_history_8_1":
			dialog.text = "�� ������ �� �� �� ������ ������� �� ���� �� ������ �������? �� ���� ���������...";
			link.l1 = "�����, ��� ������ � ��� �������: � ���� ������� ������, ������� ��� ������ ��� �������� ����� �� ��������� ���������� ������ �������� ������. �������, ��� ������� �� � ���� ���� �� �������� ������������ �� ���� ������ � �����������, �� ��� ���� �� �����. ������������� ��� �� ������ ����������.";
			link.l1.go = "Gladis_history_8";
		break;
		
		case "Gladis_history_8":
			dialog.text = "��, �������! � ���� ��� ����... � ���� � ����������� ���� �� ����, ��� �� ����� ��� �������� �����... ����������� ����, ��� ��! ����� �� ������ � ���� �������, ��� ���� ���!";
			link.l1 = "��� ����, ������ ��� �����.";
			link.l1.go = "Gladis_history_9";
		break;
		
		case "Gladis_history_9":
			DialogExit();
			RemoveItems(pchar, "chest", 1);
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Saga", "22");
			sld = characterFromId("Helena");
			GiveItem2Character(sld, "pistol5");
			EquipCharacterbyItem(sld, "pistol5");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Helena_hire":
			dialog.text = "�� ��������? � ��� ������ ����?";
			link.l1 = "�� ������� ������� �������� � ���� ����� � ���� �������� �� �������. ������� �������� ��������� ���������. ���� �� � ���� �� ����� ��� ��������, ����� ����� �������� ������. �������, � ����� �� ����������.";
			link.l1.go = "Helena_hire_1";
		break;
		
		case "Helena_hire_1":
			dialog.text = "��, ��� ������! � � �� ������������ ������� ��� �� ����. ������ ������, ��� ����, ���� ������� � �� ��������. � ��� �����-�� ����� ���� ����� ����� � ����!";
			link.l1 = "������� �� ������� �����, ������ ��� �����! � ������ ��� ���� � �����... �������� ������.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", false);//������� ������� �����
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "Helena_hire";
			pchar.questTemp.Saga = "helena2";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}