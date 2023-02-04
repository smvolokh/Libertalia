// ��� ����� �������-�����
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "�� ���-�� ������?";
			link.l1 = "�� ���, ������.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";

		break;
		
		// ������
		case "W_officer":

				dialog.text = "������������. ��� ��� ������?";
				link.l1 = "� ����� �� �������� �����. ��������, ����������� ������� � ������...";
				link.l1.go = "W_officer_1";
				break;
				
		
		case "W_officer_1":
			dialog.text = "��� � ����� �������� ������. ��� ���� ������ �� ���. �� ���������� ����� ������ � ��������� ����������.";
			link.l1 = "�������, �������...";
			link.l1.go = "W_officer_exit";
		break;
		
		case "W_officer_exit":
			DialogExit();			
			NextDiag.TempNode = "W_officer";
		break;
		

		
		// ������
		case "W_clerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "�������! ���� � ���������! �������!";
				link.l1 = "�-���!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "���� ��� ���-�� ����� - ���������� � ����� ������.";
			link.l1 = "������, � �����" + GetSexPhrase("","�") + ".";
			link.l1.go = "exit";			
			NextDiag.TempNode = "W_clerk";
		break;
		
		// ������� ����� 
		case "W_headclerk":

			dialog.text = "�� ���-�� ������, " + GetSexPhrase("������","����������") + "?";
			if (!CheckCharacterItem(pchar, "FraTradeLicence"))
			{
				link.l1 = "� ���� ���������� �������� �������� ����� ��������.";
				link.l1.go = "licence";	
			}
			if (!CheckAttribute(npchar, "quest.trade"))
			{
				link.l2 = "� ������, ��� � ��� ����� ���������� ����������� ������� � ������ �������� ����. ��� ���?";
				link.l2.go = "trade";	
			}
			else
			{
				link.l2 = "��� � ��� ������� ������� � �������? ��������, ����������.";
				link.l2.go = "trade_1";	
			}

			link.l9 = "���, ���� ������.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "W_headclerk";
		break;
		
		// �������� ��������
		case "licence":
			if (!CheckAttribute(npchar, "quest.licence"))
			{
				dialog.text = "�� ��� ��, ����������, ������������. �� � ������ ������� ��� ������������, ��� ���� �������� ������� ����� ������, ������� � ����������� ������������ ������������ ���������� �� ���� ���� �������� ��������, � ������ - ������� ����������� �������� � ��������� �������� �������� ����� �����\n� ������ ��������� ������ ����� ���� �������� ����� ���������� ������������. ����� �� �������� ���������, ���� �� �����-�� ��������, ������� �����, �������� � �������� � ����������. ��� �������?";
				link.l1 = "����������. � ����� ��� � ��������.";
				link.l1.go = "licence_0";
				npchar.quest.licence = true;
			}
			else
			{
				dialog.text = "�� ��� ��, ����������, ������������. �� ����� ���� �� ������ �������� ��������?";
				link.l1.edit = 6;
				link.l1 = "";	
				link.l1.go = "licence_1";
			}
		break;
		
		case "licence_0":
			dialog.text = "�������� ���� ����� ������������������ ����� � ����� ���� ����� �����, ��������� ������������ ���� ������ ��������� � ��������� ���� ������ �������� - ���������. ������ ���� � ��� ���� �������� � ������� � ��� ������, � ���� ������� �� �������� �������, �������� ��� �� �������. ����� ���� - � ��� �� ������ ������. ������ ���\n���� �� ����������� ��������� � ���������� ��� �������� - �� �������� ����� ������ � ���� ������� ������������� ���� - ��� ������� ��� �� �������� �������, ��������� �������� ������ � ������� � ������� ����� ���������� ������� ��������, � ������ ����� �����������\n��, ���� �� �����: �������� ����������� ��������, ������ �� �������� ������������ ������������� �������� ���������... ��, ������, ��������, ��� ���������. �� ����� ���� �� ������ �������� ��������?";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = "��������, �� ��� ��� ���� �������� ���� ������. � ������� �����.";	
			link.l2.go = "exit";
		break;
		
		case "licence_1":
			float fQty = stf(dialogEditStrings[6]);
			//npchar.quest.lcc_summ = makeint(sqrt(fQty)*10)*1000;
			// ������� � ���������
			npchar.quest.lcc_summ = makeint(sqrt(fQty)*10)*7;
			if (fQty < 1)
			{
				dialog.text = "�����, ����������, �������� �����, �� ���������� � �� �������. � ��� ����� ���������. ��� �� ������� ���� ��� ����� ��������?";
				link.l1 = "������ �������...";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 0 && fQty < 20)
			{
				dialog.text = "����������� ����, �� ������� �� ������ �������� - �������� ����. �� ������� ����� ��� �������� - �� ��������, ��� ������?";
				link.l1 = "������ �������...";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 180)
			{
				dialog.text = "������������ ����, �� ������� �� ������ �������� - �������. �� ������� ����� ��� �������� - �� ��� �����������, ��� ������?";
				link.l1 = "������ �������...";
				link.l1.go = "licence_r";
				break;
			}
			dialog.text = "�� "+FindRussianDaysString(sti(fQty))+"? ������. ��������� ����� �������� �������� "+FindRussianDublonString(sti(npchar.quest.lcc_summ))+". ��� ����������?";
			//if (sti(pchar.money) >= sti(npchar.quest.lcc_summ))
			if (GetCharacterItem(pchar, "gold_dublon") >= sti(npchar.quest.lcc_summ))
			{
				link.l1 = "��, �������, ����������.";
				link.l1.go = "licence_2";
			}
			link.l2 = "� ���������, � ���� ��� ������ � ����� ������� �����. � ����� � ��� �� ��������� �����.";
			link.l2.go = "exit";
		break;
		
		case "licence_r":
			dialog.text = "";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = "��������, �� ��� ��� ���� �������� ���� ������. � ������� �����.";	
			link.l2.go = "exit";
		break;
		
		case "licence_2":
			int iQty = sti(dialogEditStrings[6]);
			//AddMoneyToCharacter(pchar, -sti(npchar.quest.lcc_summ));
			RemoveItems(pchar, "gold_dublon", sti(npchar.quest.lcc_summ));
			GiveNationLicence(HOLLAND, iQty);
			dialog.text = "���, ���� ������... ������ �������� ������� � ������... ���, ������. �������� ��� ��������.";
			link.l1 = "�������! �� ��������, �����.";
			link.l1.go = "exit";
		break;
		
		case "trade":
			dialog.text = "����� ��� �� ��������. ����� �� ������ ���������� ������������� �������, ����� ��� ����������� ������, ����������, ��������� � �������� ���� ��� ��������� ���������� �� ������� ������� �����. ������ � ������� ��� ������ �� ������, �� ����������� ����� ��� �������� ����� - ���������, ��������� ��. ��� ��� ���� �� ������� ������, ��� ������ - ������� ����� ��������\n����� ������������ � ��� � ������� ���������� ����� ���������� � ��������� �����. ������� ���������� ����������� �� �������?";
			link.l1 = "��, ������ ��� �������.";
			link.l1.go = "trade_1";
			npchar.quest.trade = "true";
		break;
		
		case "trade_1":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 7)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);			
		break;
		
		// ������ ��������
		case "depeshe":
			dialog.text = "��, ��������...(������) ���-���... ������, �������� ���� ����, ��� �� ������� � ������... ��� �������! ��� �� ������� ��� ������?";
			link.l1 = "���������� � ������ ����������� �������. �� ��� ���, ������ �� ��������?";
			link.l1.go = "depeshe_1";
		break;
		
		case "depeshe_1":
			dialog.text = "��. ����� ���������� ����� ��� �� ��������, � ������. ��� � ������� ���������� ����... � ���� ��������� �������, ��� �������� ��� �������� �������� �� ������������ ���� - �������. ��� ���������?";
			link.l1 = "� ������� ������.";
			link.l1.go = "depeshe_dublon";
			link.l2 = "� ���� �������� ��������.";
			link.l2.go = "depeshe_licence";
		break;
		
		case "depeshe_dublon":
			TakeNItems(pchar, "gold_dublon", 700);
			Log_Info("�� �������� 700 ��������");
			dialog.text = "������. ��� ������� ��������. ������ � ��������� ��� �� ��� ������ � ����� ������ �� �����.";
			link.l1 = "����������, ���������. ��� ���� ������.";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_licence":
			if (CheckCharacterItem(pchar, "FraTradeLicence")) TakeNationLicence(HOLLAND);
			GiveNationLicence(HOLLAND, 180);
			dialog.text = "������. ��� ���� �������� �� �������.";
			link.l1 = "�������! � ��� ���� ������.";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_exit":
			RemoveItems(pchar, "Cromvel_depeshe", 1);
			pchar.quest.Terrapin_CromvelScuadron.over = "yes"; //����� ����������
			ChangeCharacterNationReputation(pchar, HOLLAND, 15);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			dialog.text = "���������. ���������, ��� �� �������� �������������� � ���������� �� ��������� � ���������. � ������ � ����� �������� ������� ���� � ������ �����������.";
			link.l1 = "�� ��� � ��� ��������� ������, �� � �� ��������. �� ��������!";
			link.l1.go = "exit";
		break;
		
		// ����� ���� ����
		case "HWIC_Boss":
			if (!CheckAttribute(npchar, "quest.silk_info") && sti(pchar.reputation.nobility) > 60)
			{
				dialog.text = "�-�, ������� " + GetFullName(pchar) + "! ����� ������, ��� �� �� ��� �����. � ���� ��� ��� ���� ������� �����������.";
				link.l1 = "����� �������! ����������� ��� ������, ������.";
				link.l1.go = "silk_info";
				break;
			}
			dialog.text = "������������, ������� " + GetFullName(pchar) + "! ��� ���� �������?";
			if(CheckAttribute(npchar, "quest.silk")) // �������� ������
			{
				if (GetDataDay() == 1 || GetDataDay() == 15)
				{
					link.l1 = "� �� ������ ������������ �����...";
					link.l1.go = "trade_silk";
				}
			}
			link.l2 = "������ ����. ���, ������ �� ���� - � ������ ����� ���������������� ���.";
			link.l2.go = "exit";			
			NextDiag.TempNode = "W_Boss";
		break;
		
		case "silk_info":
			dialog.text = "� ������� ������� �������� ����� � ����� ������ �� ����� � ����������� � ��������� �� ������ ������ ������������ �����. �� ������, ��� ��� �� �����? �� ���� ������������� ����� ������ �� ����� ������, ��� ��� ��� ��� ��������� ����� ���������.";
			link.l1 = "��������, ��� ���������� �����������. ������ �������?";
			link.l1.go = "silk_info_1";
		break;
		
		case "silk_info_1":
			dialog.text = "�������� � ���� ���� ���������, �� � ��������� �������. ��� ��� � ���� ��������� �� �������� ������� ������ ������ ��� ������. ��������� ������ ������ - �������� ������� ��������. ������� �������� ���: ������� ������� � ������������ ����� ������ � ���� ������������ ��� ��� �������� �������. ���� �� �� ������� �� ���� � ��� ��� - � ������ ������� ����������.";
			link.l1 = "�� ���� ������� ������������ � �� ����?";
			link.l1.go = "silk_info_2";
		break;
		
		case "silk_info_2":
			dialog.text = "������! ������ - ���������, ������ - ���. ��� ������ ����������� ��������� - �������� ��������. �������, �� ������� ���� ���������� �����������.";
			link.l1 = "������� �� �����������, ������. �����, � ����������� �� ������������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "W_Boss";
			npchar.quest.silk_info = "true";
			npchar.quest.silk = "true";
		break;
		
		// �������� ������
		case "trade_silk":
			dialog.text = "�������, �������. ���� ��� ����������. ������ ��� ��������?";
			if (GetCharacterItem(pchar, "gold_dublon") >= 600)
			{
				link.l1 = "�������! ���, �������� ����� ����� ��������.";
				link.l1.go = "trade_silk_1";
			}
			else
			{
				link.l1 = "��� ��������, ����� ������ �� �������. ������ �������!";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "W_Boss";
		break;
		
		case "trade_silk_1":
			RemoveItems(pchar, "gold_dublon", 600);
			Log_Info("�� ������ 600 ��������");
			PlaySound("interface\important_item.wav");
			dialog.text = "������� ����� � ���� ����, �������. ���� ����� ��������� ������ � ������ �������.";
			link.l1 = "�������!";
			link.l1.go = "trade_silk_2";
		break;
		
		case "trade_silk_2":
			dialog.text = "������� ������� ��� � ���� ��� �� ���� ���. ���������, ���������.";
			link.l1 = "�����������. �� �������!";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_SHIPSILK, 30);
			DeleteAttribute(npchar, "quest.silk");
			SetFunctionTimerCondition("Silk_TraderAttrReturn", 0, 0, 1, false); // ������
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			NextDiag.TempNode = "W_Boss";
		break;
		
		case "fight":
			DialogExit();
			sld = characterFromId("W_officer");
			LAi_SetGuardianTypeNoGroup(sld);
			LAi_group_Attack(sld, Pchar);
			for (i=1; i<=6; i++)
			{	
				sld = characterFromId("W_sold_"+i);
				LAi_group_Attack(sld, Pchar);
			}
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}