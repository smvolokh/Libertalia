// ������� ������ - �������
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
    string sTemp, attrLoc;
	
    attrLoc = Dialog.CurrentNode;
	int iSumm = 0;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	if (findsubstr(attrLoc, "RelationTo_" , 0) != -1)
	{
		i = findsubstr(attrLoc, "_" , 0);
		npchar.quest.relation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // ����� � �����
		// �������� �� ��� �������
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		if (CheckAttribute(Pchar, "GenQuest." + attrLoc) && sti(Pchar.GenQuest.(attrLoc)) == true)
		{
			Dialog.CurrentNode = "RelationYet";
		}
		else
		{
			Dialog.CurrentNode = "RelationAny_Done";
			npchar.quest.relation.summ = CalculateRelationLoyerSum(sti(npchar.quest.relation));
		}
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "� ������� ������� ������. ����������� ����� �������� � ������� ���� �������� ����������������. ��� ������ ��������, ��, ���� ��� �������, ��� ���� �����.";
				link.l1 = "�������, � ������� ������ �������� ��� ���� ��� ����������.";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "loxly")
				{
					link.l1 = "�� ��� � �����. � ���������� ���� ����� ���� ����� �� ����� ����� ��� �����, ������ ������ ��������������� �������� �����. ����� ������ �� ������ � ���� ��� ������������ ���������� ������ ����, � ���������� �� ����� �������� �������� ����-������, �������� ��� ���������. � ��� ���� ��� �������� ����� ���������, ��� �������� �������� ��������� � ����������. ������� �� ������ �� ��, ����� ������ ����� ����� ���������� ������� �� ������?";
					link.l1.go = "saga";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga"))
				{
					if (pchar.questTemp.Saga == "loxly") // ������ ��������� �� ����
					{
						dialog.text = "��� ������������� ��� ������, ���? ������, �� ���������� �������� �����������.";
						link.l1 = "��, �������������. � ���������� ���� ����� ���� ����� �� ����� ����� ��� �����, ������ ������ ��������������� �������� �����. ����� ������ �� ������ � ���� ��� ������������ ���������� ������ ����, � ���������� �� ����� �������� �������� ����-������. ������� �� ������ �� ��, ����� ������ ����� ����� ���������� ������� �� ������?";
						link.l1.go = "saga";
						break;
					}
					if (pchar.questTemp.Saga == "bakaut")
					{
						dialog.text = "���, � ��� �� ����������� � ����������� ������ ����. ��������� �����, ��� � ��� � �������.";
						link.l1 = "������.";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "molligan" || pchar.questTemp.Saga == "sellbakaut")
					{ // ���� �� �������� �� ����� ����� �� �������
						dialog.text = "���, � ���������, ��� ������������� ������ �������, ����� ��������� ������ ������ � �������. � ��� �� ����� � ���������. ����������, ��������� �����.";
						link.l1 = "������.";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "removebakaut") // � �������� �����������
					{
						// ��������� �������� �������
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							RemoveItems(pchar, "map_sharp_full", 1);
							dialog.text = "������, �� ��� �� �� ��� �����! ������ ��� ��� ����� �������������� ��������. ���� �������� ��������� �����, � ���� ������ ������ �� ������ ����������� ���������� ������. ������ ��� ����� ������� ����."
							link.l1 = "��� ��� ��!.. ����������, ��� �������� ����� ������...";
							link.l1.go = "saga_l3";
						}
						else
						{
							dialog.text = "�, ��� � ��, ���. � ����������� � �����������, ��� ��� ������ ���� �� �������. �������� ������?";
							if (GetCharacterItem(pchar, "gold_dublon") >= 450)
							{
								link.l1 = "��, ������. ��� ���� �������.";
								link.l1.go = "saga_5";
							}
							else
							{
								link.l1 = "����� �������� ��� ������������ - ������� � ������� �� �������. ������ �������.";
								link.l1.go = "exit";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "shadow")
					{
						// ����� �������� �������
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							dialog.text = "������, �� ��� �� �� ��� �����! ������ ��� ��� ����� �������������� ��������. ���� �������� ��������� �����, � ���� ������ ������ �� ������ ����������� ���������� ������. ������ ��� ����� ������� ����."
							link.l1 = "��� ��� ��!.. ����������, ��� �������� ����� ������...";
							link.l1.go = "saga_l3";
						}
						else
						{
							dialog.text = "���, ��� ������� �������� ���-������ ������������ ������������� ����� ��������������?";
							if (!CheckCharacterItem(pchar, "Letter_beatriss"))
							{
								link.l1 = "���� ���. �� � ������� ��� ����.";
								link.l1.go = "exit";
							}
							else
							{
								link.l1 = "��. ������ � ���� �� ����� �������������� �����, ��� �������������.";
								link.l1.go = "saga_14";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "court" && GetNpcQuestPastDayParam(npchar, "court_date") >= 1 && IsOfficer(characterFromId("Helena")))
					{
						dialog.text = "�-�, ��� � ��, ���. ��� ��� ������. ����������, � ��� ��� ��������. ��� � ���� ���� ��������������?";
						link.l1 = "��. ��������� ����������� - ����� ��� �����.";
						link.l1.go = "saga_26";
						break;
					}
					dialog.text = "��� ������������� ��� ������, ���? ������, �� ���������� �������� �����������.";
					link.l1 = "�������, �� ���� � ���������� �� ������ ������ ���.";
					link.l1.go = "exit";
				}
				if (CheckAttribute(npchar, "quest.waitgold"))
				{
					dialog.text = "������������, ���. ��, ��� � �������, �������� ��� ��� �������?";
					if (GetCharacterItem(pchar, "gold_dublon") >= 450)
					{
						link.l1 = "��, ������. ��� ���� �������.";
						link.l1.go = "saga_36";
					}
					link.l2 = "������ ���, ������ ������, � ��� ��������... � �����, � ���� ����� ������, 900 �������� �� ���� ������ - ��� �����, ��� ����������.";
					link.l2.go = "saga_38";
					link.l3 = "������ ������, � ��� �����. ������� ������� �����...";
					link.l3.go = "exit";
					break;
				}
				dialog.text = "��� ������������� ��� ������, ���? ������, �� ���������� �������� �����������.";
				link.l1 = "�������, �� ���� � ���������� �� ������ ������ ���.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "saga":
			// ������ �������� �������. �������� �����, ������ ��������� ���, ���� ���� �� ��������, �������� ��������
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				RemoveItems(pchar, "map_sharp_full", 1);
				dialog.text = "������, ��, ��������, ����� �� ���� �� ���� � �� �������� ��������? ���� ������ ������ - ������� ���� ����������� �����! ��, ��������� ����� ������������, ������ ����, ��������� � ��� ��� ������������ ���� �� ������, �����, � ���� ������ ������ ���������� ������. ���!"
				link.l1 = "��� ��� ��!.. ����������, ��� �������� ����� ������...";
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = "������� ���������� �� �������� ����� ��������? ��... ������, ���� ������� ���� ���������. ���� ������ - ��� ��� ����������� ���������� �������...";
				link.l1 = "��� ���. �������� ���������, �������, ������������ ��� ��������� ����� ���� ������ ���� �������� �����, ���������� ���������� �������. � ��� ���� ��� �������� ����� ���������, ��� �������� �������� ��������� � ����������. ";
				link.l1.go = "saga_1";
			}
		break;
		
		case "saga_1":
			dialog.text = "������� ����... ���-���. ������ ��� ���������� � ����, ��� ����� �������������� �������� ����� � ������������ � �����������, ����������� ���� ������. ����� ��� ���?";
			link.l1 = "��� ���, �� � �� ��� ��� ������ ����� ����, ��� �� �������� � ���� ����������. ��� ��� ���������� ������ ����� �����?";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			dialog.text = "��� � ��� ������ - ���� �� �� ������. �������� ����� �� ������ - �� �� �� �����, ��� �������� ������ ������ ��� ������ �� ������. � ���� ��, ������� ���� ��� �������, � ���� ������� � �� ������������� ������������ ������.";
			link.l1 = "�� �������� ��� ���������� �����, ����� � ������� ����, �� ���� ��� ��������?";
			link.l1.go = "saga_3";
		break;
		
		case "saga_3":
			dialog.text = "������, ������������� ����� ����������� � ��������. � ���� �� ����, ��������� ������� �� �����. �� ������ ������ ������ �����: ��������� ��������� ��������. � ����������� �� ����, ��� ������ ���� ����, ��� ����� �������� ��� ��������\n��������� ����� ������ � �������� - � ����� ������ � ���� �� ���������. ����� � �������� � ���� ����������. ��� ����������?";
			link.l1 = "��� ������������� ��� ��� ������� ��������, ������� ����������. �� ������� ����� ������!";
			link.l1.go = "saga_4";
		break;
		
		case "saga_4":
			DialogExit();
			pchar.questTemp.Saga = "bakaut"; // ��������� ����
			AddQuestRecord("Testament", "2");
		break;
		
		case "saga_5":
			RemoveItems(pchar, "gold_dublon", 450);
			Log_Info("�� ������ 450 ��������");
			PlaySound("interface\important_item.wav");
			dialog.text = "����� ������. � ����� ����� ���� ���� � ������������ �������� � ����. ������ ����������. � ������ ��������� � ������ � ��������� � ������� ������. ���� � ���������� ����� ������� ���� ���������. ������, ��� ��� ������� ����� ��� ��������� �����. �� ����� ����� ���� ������������\n����� ����, ��� ����� ����, ��� ������� ������ �� �� �����, � ���������� ����� ������� ����� �� ������ ����-������, ��� �� ������ ����������� ������������ ������� ������� ������� ���� � ���� ������.";
			link.l1 = "�� �������� ������� ������ ��� ������� ����� � ����� ��� ����� �� ���� ������!";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "�������� �� �� � �����, �� � ������ ��������� �������� ���� ������ ��������. ���������, ��� ����������, ����������� ������ ������ ��� �������. � � ����� �������, ��� � �����, ������� ������. ��� ����� - �� ��� �������?";
			link.l1 = "��� ������� �� ��������� ����, �� ����� ����� ������ ������� ����, ��� ��� �������� ������ ������� �������� �������� ����, ������ ��������.";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "���������! �� ��� ��� ������ ����������� ��� ��������? �������� �������� ����� ���� ����� ������� � �������� ����?";
			link.l1 = "��������� � ����� - ���. ������ ��� ����� ������ �� ������� ������, � ������ ����� ���� ������ � ����� �������.";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "��� �����. ������ ��, � ������ ��� ���� ���������� � ���, ��� � �������� ���� ���� ������ ����������. ��������, ��� � �������� ������� ��� ������ ������� ����������� ������. ���� ����� ����� ��������� ������ ����� � ������������ �� ����� ������ ��� �������.";
			link.l1 = "�� ������ � ����� ���� ������ ����� ��������!";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "��� ������� ������ � �� ������, � ���, ��������, ���� �� ����������, �� ���� ������� ������������� ������ �� ����-������. ������� ������� �������� ���� ���� � ������, � � ������ ����� �����-�� ��������, ���������� �� �����, ������� �� ����������� ���� �������� ������, ���������� �� ���������� ���� ����� ������... �-�-�, ��� ��?";
			link.l1 = "�������. ������ �������, �������� ������.";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			dialog.text = "��� ������. ���� � ��� ����������� ����� ���-���� ��������? ";
			link.l1 = "������ ��. ������� ��� ������. ���� ������ �������, ����� ����� ��� ���� ��� ������� �����. ���� �����, ������ ����� ����-������ ���� �� ���-�� ������� �� ����� ������. �� ��� ���������, ��� ����� �� ����.";
			link.l1.go = "saga_11";
		break;
		
		case "saga_11":
			dialog.text = "��. ��� ��� ������ �������� ���. ����� ���, ��������, ������� ������. � ���� ������������ � ��� ��������. ������ �������� � ������������ �������. �� ��� ��, ��������� ������� �� �������, � � �������� �������� ������� - �����, ���-������ �� � ��������.";
			link.l1 = "������. ��� � ��������.";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "������� ����� �����, � ������������ � ������� - ��������, � ��� ������� �� ������� ����� �����-�� ������ ���� ����� ��������������. �����, ���� ���������� ������������� �� �����������. ";
			link.l1 = "��, ���� �� ��� ������������� ���������. �����, �� �������, ������ ������.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			DialogExit();
			RemoveItems(pchar, "map_sharp_full", 1);
			pchar.questTemp.Saga = "shadow";
			pchar.questTemp.Saga.Shadows = "sentjons";
			AddQuestRecord("Shadows", "1");
		break;
		
		case "saga_14":
			dialog.text = "��� ���? ������� ���������, ��� �� ��� �� ��������������.";
			link.l1 = "��� ������ ������ �������� ���� ������ �����, � ������� ��� ���������� ����������, ��� ������ ���� �� �������� ��������, ����������, ��� ������� �����, � ������ �� �� ��������� ������� ����� ������ �������. ��� ��� ������, �������...";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			RemoveItems(pchar, "Letter_beatriss", 1);
			dialog.text = "";
			link.l1 = "���� ������ ������ ����������� ���� �������� �� ������� ��� ��������. � ����� ��, ��� ���� ������� ������������ �� ������ ��� ������� �����.";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) // ������� ����
			{
				dialog.text = "���������! �������� ����� � ������ ���������� ��������� ������� ����� ��� ������� � ����� ����-������ �������� ��� �����. � ������� �������, ������� ������� �����, ���������� ����� ������ �������. ����� ���� ������ ��� ����� � ���������� ��������� ������������ ���������!";
				link.l1 = "��! �������, ����� �� � �����... � ���� ���� ���������� ��������� �������� �������, ������� ������ ����-������, � ���, ��� �� ��� ������� ������ �������� ��� �������� ������������ ����� ������! ���, ������������...";
				link.l1.go = "saga_17";
			}
			else
			{
				dialog.text = "���������! �������� ����� � ������ ���������� ��������� ������� ����� ��� ������� � ����� ����-������ �������� ��� �����. � ������� ������� ��� � ������, �������� ���� �� ������ ��������� ����-�����. ����� ���� ������ ��� ����� � ���������� ��������� ������������ ���������!";
				link.l1 = "��! �������, ����� �� � �����... � ���� ���� ���������� ��������� �������� �������, ������� ������ ����-������, � ���, ��� �� ��� ������� ������ �������� ��� �������� ������������ ����� ������! ���, ������������...";
				link.l1.go = "saga_17";
			}
		break;
		
		case "saga_17":
			RemoveItems(pchar, "letter_baker", 1);
			dialog.text = "��. ���-���...";
			link.l1 = "����� ���������, ������? ����� �������, ����� ������� ���, �������� � ������, ��� ����� ���� ���������� ��������� ���������. ��� ���� ������ �� � ������ ���� �����, �� �������� �����.";
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "saga_18";
			else link.l1.go = "saga_22";
		break;
		
		case "saga_18":
			dialog.text = "�� ���... ��� � ����� ������ ����! ���� �� �������� ��������� ������ ��������, �� ��� ���������� ��������, ��� ��� ��� ����� ������� ���������� ������ ������� ������� ������ ������, �������� ������ ��� ���������� ���������� � ������� ���� �� ������� ������������!\n� ��������� ������� ������ ��������� ����� ������ ������! ��� ��� ��! � ������ �������� �� �������� ����� �������!";
			link.l1 = "� ����� ���. ��������� ��������� � ������� �������� �� ���. ��, �������, � ��� ����� ������� ������?";
			link.l1.go = "saga_19";
		break;
		
		case "saga_19":
			dialog.text = "��� ������ �������, ���. ��� ����� � ����������� ������� � �����, ������������ �� �����. ������ ���� �����������, ��� ����� ��� �������� ����� ������������ ��������. �������, �� ��� ���� ������ �����, ��� ����� ����� ����� �� �������. � ��� ���� ��� ���� � �������� ������ �����. � �� ����� �����! �� �������������?! �� �����!";
			link.l1 = "��, ������. ����������, ��� �����... �� ���?";
			link.l1.go = "saga_20";
		break;
		
		case "saga_20":
			dialog.text = "����������. � ���� �� ��� ��� ��� ���������... ����������� ������, ������������� ����, ������, ��� �� ���� ���� �� ���� �����������. ������� ���� ��� �� ������, ��� �� ����, ��� �� ����-�� ���. � �����, ���������� ������.";
			link.l1 = "�������... ����� ��������� ���?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_21":
			dialog.text = "��� ������ ������� �� ���, ���. ��� ������ �� ��������� ��� ������ ����� �������� - 450 ��������, � ����� ��������� � ��� � ����������� ������ ������ ��������. �� �����, ��� ����� ������ ����� ������ ������, ����� ������ � ����� ����������.";
			if (GetCharacterItem(pchar, "gold_dublon") >= 450)
			{
				link.l1 = "����� ������. ������� ���� �������.";
				link.l1.go = "saga_24";
			}
			else
			{
				link.l1 = "��, �������. � ������� ��� ������ �����.";
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_23";
			}
		break;
		
		case "saga_23":
			// ������ �������� �������
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				dialog.text = "������, �� ���� ��������! �� ������� ����� ���, ������ ��� � ��� ����������� � �����, �� ��-�� ����� ���������� � ������� ������ ��� ��� ����� �������������� ��������! ���� �������� ��������� �����, � ���� ������ ������ �� ������ ����������� ���������� ������. ������ ��� ����� ������� ����."
				link.l1 = "��� ��� ��!.. ����������, ��� �������� ����� ������...";
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = "�� �������� ������ ����� ��������, ���?";
				if (GetCharacterItem(pchar, "gold_dublon") >= 450)
				{
					link.l1 = "��, �������. ������� ���� �������.";
					link.l1.go = "saga_24";
				}
				else
				{
					link.l1 = "����� �������� ��� ������������ - ������� � ������� �� �������. ������ �������.";
					link.l1.go = "exit";
					NextDiag.TempNode = "saga_23";
				}
			}
		break;
		
		case "saga_22":
			dialog.text = "�� ���... ��� � ����� ������ ����! ���� �� �������� ��������� ������ ��������, �� ��� ������������� ��������, ��� ������� ������� ������ ���� ���������, ��� ������ �����, � ����� ������� �� ����� �� ������� ������������!\n� ��������� ������� ������ ��������� ���! ��� ��� ��! � ������ �������� �� �������� ����� �������!";
			link.l1 = "� ����� ���. ����� ��������� ���?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_24":
			RemoveItems(pchar, "gold_dublon", 450);
			Log_Info("�� ������ 450 ��������");
			PlaySound("interface\important_item.wav");
			dialog.text = "���������, ���. � ���� ������� ����� ����. ������ ����������� ���: ��������� �� ��� ������. ��-��, �� �� ���������� - ������! � ���-���� ������ ������� �� ����������, � � ���� ������� �����\n��������� ����������� ������ �� ����� ��������������� - ��� �� ���������, ��� �� ������� ��� �� ����� ����������. �� ����������� � �� ��������� �����. � ���� ������� - ���������� ��������� ����� �������� - � ��������� ������ � ����� ������.";
			link.l1 = "������. �� ����� � ����� ������� ������, ������ ������.";
			link.l1.go = "saga_25";
		break;
		
		case "saga_25":
			DialogExit();
			SaveCurrentNpcQuestDateParam(npchar, "court_date");
			pchar.questTemp.Saga = "court"; // ��������� ����
			AddQuestRecord("Testament", "10");
			NextDiag.CurrentNode = "First time";
			// ��������� ������ �� ������
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", true);
			LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", true);
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", true);
			pchar.GenQuest.CannotWait = true;//������ ��������
			// ������� ����� ������ ����!
			pchar.quest.Saga_TimeOver.over = "yes";
		break;
		
		case "saga_26":
			dialog.text = "��� �����? ���, ������� - ����! �� ��� ��, �������� �� ����!";
			link.l1 = "...";
			link.l1.go = "saga_27";
		break;
		
		case "saga_27":
			DialogExit();
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto10");
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			sld = characterFromId("Helena");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(npchar, "reload", "reload1", "Saga_CourtGo", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			LAi_ActorFollow(sld, npchar, "", -1);
			NextDiag.CurrentNode = "saga_28";
			// ��������� ������ �� ������
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false);
			LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", false);
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//����� ������ �����
		break;
		
		case "saga_28":
			dialog.text = "�� ��� ��, ��������� ��� ���������� ���, ���, � ���� ��������������. ������ ��� ������������ ��������� ���� ������. �� ��� ����� ������ �����������!";
			link.l1 = "����������, ������ ������. ���� ���� ���� ������ ������������. � �����, ���������� ����� ������ ����, ����� �� �������� ����, ��� ������� ����� � ������� ������� - ���� � �� �� ����.";
			link.l1.go = "saga_29";
		break;
		
		case "saga_29":
			dialog.text = "��, ������� ����� �������� ������������ � ������ � ������� ���� �� ���� ������. � ��� �� ��������? ����� - ���� �����, � �� ���������� ��� ����, ������� ���������� ����������.";
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die"))
			{
				link.l1 = "��� ������, �������������� ����� ����� �� ������ � �������?";
				link.l1.go = "saga_30";
			}
			else
			{
				link.l1 = "� ������, ��� ����� ����� ������������ �� ������ �������� ��������. ��� � �������, ��� ������ ���� ��������?";
				link.l1.go = "saga_34";
			}
		break;
		
		case "saga_30":
			dialog.text = "�������, ���. � ����� �������� ������ ������� � ���. ������ ���� ������� - ����� ���� �� ��������.";
			link.l1 = "����� ������...";
			link.l1.go = "saga_31";
		break;
		
		case "saga_31":
			dialog.text = "��� ��, � �������� ���� ������. ���� ���� �������, �� ����������� �������� �� ����������. ������, ���, ��� �������� ������ ���������� ������������� ������ �� ����. � ��� �� ������� - �������, ��� ������ ��� ���� ������� �� �� �����. ��, �����, � ������� ������ �� ������� ����������� �������� ��� 450 ��������\n����� ����, ����� ������, ��� ��, ����� ������ ������ ������������ �� ������� ������. � ������� � ���� ������: � ���� ����� � �������� ���� ����� �� ����������, ������� ����������, ��� ��� ����� �������� ����� ���� �������.";
			link.l1 = "�������. ���� �����, � ���� ����������.";
			link.l1.go = "saga_32";
		break;
		
		case "saga_32":
			dialog.text = "������������� ��������� ����������, ���� � ����� ������� ���������.";
			link.l1 = "��� � ������. � ������ ��������� ����������� - � ��� � ������ ��� ����� ����� ���.";
			link.l1.go = "saga_33";
		break;
		
		case "saga_33":
			dialog.text = "�� �������, ���.";
			link.l1 = "�� ��������, ������ ������.";
			link.l1.go = "saga_35";
		break;
		
		case "saga_34":
			dialog.text = "�����, �� - ���� �� �� ������� �����, ��������� � �����. ������ ������ ��� ��� � ����-����� - ��, �� ���� �������, ����� � ����� �������. �� ����� �� ��� ��� ��������, � �� ����� ������� ��� ������ �� �����������.";
			link.l1 = "�������... ��� ������, �������������� ����� ����� �� ������ � �������?";
			link.l1.go = "saga_30";
		break;
		
		case "saga_35":
			DialogExit();
			pchar.GenQuest.Piratekill = sti(pchar.GenQuest.Piratekill)-20;
			SetFunctionTimerCondition("Saga_RemainGoldLoxly", 0, 0, 10, false); // ������ �� ������ �����
			DoQuestReloadToLocation("PortRoyal_town", "quest", "quest3", "Saga_HelenaIslaTesoro");
			npchar.quest.waitgold = "true";
			pchar.questTemp.Saga = "lastpages";
			NextDiag.CurrentNode = "First time";
		break;
		
		case "saga_36":
			RemoveItems(pchar, "gold_dublon", 450);
			Log_Info("�� ������ 450 ��������");
			PlaySound("interface\important_item.wav");
			dialog.text = "�����������! ����� ������� ����� � ���� ����, ���! ������ �� ������ ���������� �� ��� �� ����� �������� � ������������ �� ������. �������� � ������� ������ �� ������� �� ������... ����������, ���������. ������ ���� ��� ��� ������.";
			link.l1 = "�����, �������, �������� ��� ������������� � �������, ��... ���� ��. ������� � �� ��������, ������ ������.";
			link.l1.go = "saga_37";
		break;
		
		case "saga_37":
			DialogExit();
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //����� ������
			NextDiag.CurrentNode = "Loxly"; // ������ ��������
		break;
		
		case "saga_38":
			dialog.text = "�� ��� ������ � ���, ������? �� ������ �������� ������� ������ ��������?";
			link.l1 = "������. ��� �������� ������ ������ �. �� ���� �� �������������, ���� ��� ������ ������� ���������� ��������������. � �� ������ ������� ������� � ���� � ��������� � ����. ��������� �������� �� ���, � ������, �����, ��� ����������.";
			link.l1.go = "saga_39";
		break;
		
		case "saga_39":
			dialog.text = "�� ��������������, ��� ��������� �����, ������! ��� ��, � �� ������� �� ���� ���������� ���������� ��������, � �� �� �����������. �� �������� �� ������� ������! � ��������, � ��� ���������... ���������� �������� ��� ��� � ������ ������� ����� �� �������������!";
			link.l1 = "��� � � ��������� �������. ����� �������, ������ ������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //����� ������
			LocatorReloadEnterDisable("PortRoyal_town", "houseSp4", true); // ������� ���� � ������
			ChangeCharacterNationReputation(pchar, ENGLAND, -10);
		break;
		
		case "saga_40":
			dialog.text = "� �� ����� � ���� �������������. ����������, ���� � �� ������ ������!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
		break;
		
		// ������� ����
		case "saga_l3":
			dialog.text = "���, ���� �� �� ������ �� ��� �������� - �� �� ����� �������� ����, ��������� �������� ���� ������ �������. ��� ����� ����.";
			link.l1 = "��, � ���-�� ��� ����! �����, ��������, ������ ������.";
			link.l1.go = "saga_l3_1";
			// ����� - � ���������
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l3";
		break;
		
		case "saga_l3_1":
			DialogExit();
			pchar.quest.Saga_Late_3.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_3.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_3.function = "Saga_HelenaTalk";
			Saga_ChangesIslatesoro(); // ����� ������������ �� ����-������
			pchar.questTemp.Saga = "late_l3"; // ��� ��������
		break;
		
	//-------------------------------------- ����������� ������ ------------------------------------------------
		case "Loxly":
			dialog.text = TimeGreeting()+", ���. ��� ��� ������. ��� ������������� ��� ������?";
			link.l1 = "��. ������ �� ���� � � ��� � ������.";
			link.l1.go = "loxly_1";
			link.l2 = "���, � �������, ���� ������ �� �����. � ������ ����� ������������� � ����.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "loxly_1":
			dialog.text = "� ����� ��� ���������. ������ ���� ������ ��� �����?";
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
			{
				link.l1 = "� ���� �������� ��������� ������������ � ����������� ��������.";
				link.l1.go = "RelationTo_0";
			}
			
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
			{
				link.l2 = "� ���� �������� ��������� ������������ � ������������ ��������.";
				link.l2.go = "RelationTo_1";
			}
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
			{
				link.l3 = "� ���� �������� ��������� ������������ � ���������� ��������.";
				link.l3.go = "RelationTo_2";
			}

			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
			{
				link.l4 = "� ���� �������� ��������� ������������ � ������������ ��������.";
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "� ������ ����������� � ����������������.";
				Link.l5.go = "contraband";
            }
			Link.l7 = "��������, �� � ���������...";
			Link.l7.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "RelationYet": // ��� ��������
			dialog.text = "� ��� ������� ��� ����� �����. ��� ����� � �������, ������ ���.";
			Link.l1 = "�������. ���� �����!";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		// --> ������ ���
		case "RelationAny_Done":
			iSumm = sti(npchar.quest.relation.summ);
			int iRate = abs(ChangeCharacterNationReputation(pchar, sti(npchar.quest.relation), 0));
			if (iRate <= 10) sTemp = "��, ���������� �������������� ��� ����� �� ��������. �������������� ������. � ��� ����� ����� ���� �����������";
			if (iRate > 10 && iRate <= 30) sTemp = "��, ���� ��������� ����������, �� ������ ���������� � �� ����. � ��� ����� ����� ���� �����������";
			if (iRate > 30 && iRate <= 60) sTemp = "��, �������� �� ������� �������. �������� �����������, �� � ������, ��� ����� ��� ����� � ��������� ������� ���� �����������";
			if (iRate > 60 && iRate <= 90) sTemp = "� ��� �� ��� �� ��� ����������, ���? ������������ �� ������ ��������� - ��� ����� ���������. ������ ��� � ������ ���������� ��� � ���� ����. ��� �������� ����� �����������, ����� ������� ���� �����������";
			if (iRate > 90) sTemp = "�� ��... �������� ���������������� - �� ��������� ������ ����� ����� ����. ��� ����� ������ ������, �� � ���-���� ������ ������� �� ������� - � ����� ���� �����������";
			dialog.text = ""+sTemp+" � "+XI_ConvertString(Nations[sti(npchar.quest.relation)].Name+"Abl")+". ��� ��������� ��� � "+FindRussianMoneyString(iSumm)+".";
			if(sti(pchar.money) >= iSumm)
			{
				link.l1 = "������, ������ ������, � ��������. ��� ���� ������ � ������ �������� ��������.";
				link.l1.go = "relation";
			}
			link.l2 = "� ���� ������ ��� ��������� �����. � ����� �����!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;

		case "relation":
			dialog.text = "������� ����� � ���� ����, ���. ������ ����� �������� - �� �����, ��� ����� ��� ������ �� ������� ������ �� ���� ��������. ������������ ������� - ��������� �������� ������ � ������������ � "+XI_ConvertString(Nations[sti(npchar.quest.relation)].Name+"Abl") +", ���� � ����� ������, ����� �� ��������� ����.";
			link.l1 = "������, � ���� ���� ��������������. ������� � �� ��������!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.relation.summ));
			ChangeNationRelationFromRelationAgent(npchar);
			attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
            Pchar.GenQuest.(attrLoc) = true;
			Pchar.GenQuest.(attrLoc).loyer = "true";
			NextDiag.TempNode = "Loxly";
		break;
		// <-- ������ ���
		
		case "contraband":
			npchar.quest.contrasum = makeint(0.3*stf(Pchar.rank)/stf(Pchar.reputation.nobility)*60000);
			dialog.Text = "�� � ����� �� �� ��� �������? �������������� - �������� ������, ��-������ �������. � ����-�� ���� ����, � ������ ���� �������... �����, �������� ���� ��������, � ��������� ��� ����� � "+FindRussianMoneyString(sti(npchar.quest.contrasum))+".";
			if(sti(Pchar.money) >= sti(npchar.quest.contrasum))
			{
				Link.l1 = "������, ������ ������, � ��������. ��� ���� ������.";
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "� ���� ������ ��� ��������� �����. � ����� �����!";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "������������, � ��� �����. ��� ����� ����� � ���� ����.";
			Link.l1 = "�������!";
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, 25);
			AddMoneyToCharacter(pchar, -sti(npchar.quest.contrasum));
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}