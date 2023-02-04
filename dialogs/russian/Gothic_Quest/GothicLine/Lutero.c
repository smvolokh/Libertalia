// ������ ��������
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
			if(PChar.Gothic_Delivery == "END")
			{
				dialog.text = "�-�, ��� ��, ������� "+ GetFullName(Pchar)+". ��� ���������?";
				link.l1 = "����� ����. �����, ������.";
				link.l1.go = "exit";
				break;
			}
			
			if(PChar.Gothic_Delivery == "14")
			{
				dialog.text = "��, ��� ����, "+ GetFullName(Pchar)+"?";
				link.l1 = "����� ������������. � ����� ���� ����, �� ���� ������ ��� ������� �� �������.";
				link.l1.go = "22";
				
				if(sti(PChar.money) >= 200000)
				{
					link.l2 = "�� � ������ ����. ���� �� ��� �����, � ���� ������ ����� ��� ������� �������. ��� ���.";
					link.l2.go = "25";
				}
				
				break;
			}
			
			if(sti(PChar.Gothic_Delivery) >= 11)
			{
				dialog.text = "� ��� ��, "+ GetFullName(Pchar)+". ��� ��� ������ ��� ����� ����� ������?";
				link.l1 = "� ������� ��� ���, �� ����������.";
				link.l1.go = "exit";
				break;
			}
			
			if(PChar.Gothic_Delivery == "10")
			{
				dialog.text = "� ��� ��, "+ GetFullName(Pchar)+". ������ ������ ���, � ���� ������ �� ���� ������.";
				link.l1 = "���� � ���-��� �����" + GetSexPhrase("","�") + ". ���� ��� � ������� � ����������...";
				link.l1.go = "18";
				break;
			}
		
			if(PChar.Gothic_Delivery == "8")
			{
				dialog.text = "� ��� ��, "+ GetFullName(Pchar)+". ������ ������ ���, � ���� ������ �� ���� ������.";
				link.l1 = "�����, ������� � ���� �����.";
				link.l1.go = "exit";
				break;
			}
		
			if(PChar.Gothic_Delivery == "7")
			{
				dialog.text = "������� ���������� ���� �� ������ �����������.";
				link.l1 = "���... �� ��� ������.";
				link.l1.go = "1";
				break;
			}
		
			dialog.text = "��� ��� ����?";
			link.l1 = "������.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "1":
 	PlaySound("VOICE\Russian\GOTHIC\GG_HALLO_M\GG_HALLO_M_1.wav");
			dialog.text = "";
			link.l1 = "��� ��...";
			link.l1.go = "1_2";
		break;

		case "1_2":
 	PlaySound("VOICE\Russian\gotica\LUTERO\DIA_LUTERO_HALLO_13_00.wav");
			dialog.text = "���� ����� ������, � ������ ����������� ����...";
			link.l1 = "";
			link.l1.go = "1_3";
		break;

		case "1_3":
 	PlaySound("VOICE\Russian\gotica\LUTERO\DIA_LUTERO_HALLO_15_01.wav");
			dialog.text = "";
			link.l1 = "����� ������ �� �����������?";
			link.l1.go = "1_4";
		break;

		case "1_4":
 	PlaySound("VOICE\Russian\gotica\LUTERO\DIA_LUTERO_HALLO_13_02.wav");
			dialog.text = "��, � �������� ������, ��������� ����, � ����� ������������� ���� ����� ����������� ������� ���� ��������.";
			link.l1 = "";
			link.l1.go = "1_5";
		break;

		case "1_5":
			dialog.text = "��� ������?";
			link.l1 = "��� �� - �� ��� � �����. ���������� ����...";
			link.l1.go = "1_6";
		break;
		
		case "1_6":
			dialog.text = "������, ����� ���������.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("GothicDeliveryLuteroFirstSitDialog");
		break;
		
		case "3":
			dialog.text = "����, ��� ���� ������?";
			link.l1 = "���� ���������� ������, ������.";
			link.l1.go = "4";
		break;
		
		case "4":
			dialog.text = "����� ����������? � ��� ��, ������?";
			link.l1 = "�� ������������, ��� �� ����� �� ������.";
			link.l1.go = "5";
		break;
		
		case "5":
			dialog.text = "������, ���������, �� � ������������� �� �������, � ��� �� ��������. �����, ����������� ����������, � �� � ������ ������ ������ �� ����.";
			link.l1 = "��� ���� ���� � ���-������ �������?";
			link.l1.go = "6";
		break;
		
		case "6":
			dialog.text = "�������, �� � ��� ������ �������� �...";
			link.l1 = "������  �����! ��������� ���� ����� ���� ����� �������� ���������� ����� � ��� �� ����. ��� �� �������� ��, ��� ����������� �� ������ �������, � ��...";
			link.l1.go = "7";
		break;
		
		case "7":
			dialog.text = "...(���������)... ���? ��������, ������, ��� �� ���� �� �����?! ����� ������, ���� ����? � ������� ��������, ����� ����������� � ������, �... ������, �� ������, ��� ����� ���� ����?";
			link.l1 = "��, ����. ��������, �������?";
			link.l1.go = "8";
		break;
		
		case "8":
			dialog.text = "����! ׸���� �������! �� ���� �������. �� ���� ��������, ���� ������.";
			link.l1 = "�������?";
			link.l1.go = "9";
		break;
		
		case "9":
			dialog.text = "������ ����, ���������. �� ����, ������� �� ��������� � ���� �����, ���� ����� ��������� ���������������, ������� ������ ���� ��������� � ������ ������� ������ �� 200 000 ����. �� ���� ������� ����! �� ������ �������� �� ���� ������, ������� ����� �������� ����� ���� �����������. \n � ����� ����, ��� �� �� ���������, �������� ����� ����, ����� ��� ���������, � ��� ������ ����-������ � ��������.  ��, �����, ������, ��� � ��� ����� ���� � ���, ��� ��� ���������? � ������ ����������� ����� ���, ���� ��� �� ������ ��� ���������� ����� �����. ������ ��� �� ����� �, ��� �� ���������� ��������� � ������ ����.";
			link.l1 = "��... �� ��������, ��� ����� ��������� � ������? ��� ����� ��� ������� ����� ��������������?";
			link.l1.go = "10";
		break;
		
		case "10":
			dialog.text = "����� ������� � ��� ������, �� 200 000, ������� ��� ������ ���� ��������� ��� �� ������� ������ ������������ �����. ������ ����� ������ � 30 000 �� ���������, � ����� ��� 200 000. ��� �� � ������� �� �������, ������-�� ��������.";
			link.l1 = "��� ������, �� ������� � ���� ����!";
			link.l1.go = "11";
		break;
		
		case "11":
			dialog.text = "���, ��� �� �����������, ��� ������ ��������, � ��� ���� �������! ��� �� �� �����, ��� � ���� ������ �������� ��� �������. �������!";
			link.l1 = "�� ��, ��� ������ ���� �������������.";
			link.l1.go = "12";
		break;
		
		case "12":
			dialog.text = "������, �������� ��� ����������� �  ������? �� � �������� ������ �������, �� � ������� ����� �� � �������.";
			link.l1 = "� ��������. ��� ����� ������?";
			link.l1.go = "13";
		break;
		
		case "13":
			dialog.text = "���� �� ����? ���� ��������.";
			link.l1 = "� ���� ��������� � ���� �����, � ����-�-�����?";
			link.l1.go = "14";
		break;
		
		case "14":
			dialog.text = "� ��� �� ��� ��������� �����? ����� ��� ����� �� �����, ��� � ���� ������ �� ������������� ������������.";
			link.l1 = "� �� - ���� ��������� ����, � ����-�-�����, �����, ����-������ �� �����.";
			link.l1.go = "15";
		break;
		
		case "15":
			dialog.text = "�����, ��������? � � ���� �� ����� ������� �����������...";
			link.l1 = "�� ������� � ���� �������.";
			link.l1.go = "16";
		break;
		
		case "16":
			dialog.text = "� ���������, ��� �����-�� ����? ������ ����� ��������.";
			link.l1 = "������� "+ GetFullName(Pchar)+".";
			link.l1.go = "17";
		break;
		
		case "17":
			dialog.text = "��, �����, ������� "+ GetFullName(Pchar)+".";
			link.l1 = "�� �������.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("GothicDeliveryLuteroDialogExit");
		break;
		
		case "18":
			dialog.text = "...(���������)... ��� ���� �������! �� ����� ���� ����������, ���������.";
			link.l1 = "���� ������ ��� ������ ��������� �������� �����, � ��� ��� �����, �� ��������� ����� ���, ����� �� �������. ����� � �������� � ��������� �����, �� ��� ��� ����. ��� ������� �������� �����, � � ������ �� ��� � ����� ������. ���, ������.";
			link.l1.go = "19";
		break;
		
		case "19":
			TakeNItems(PChar, "BaltramNotice", -1);
			TakeNItems(PChar, "AkilKillersNotice", -1);
			dialog.text = "...(������)... ''� �� �������� ���������� �������� �����''.";
			link.l1 = "��� ����� ������ ��� �����. ���� � ����� ���� ��������, � ������ ��� ��� �����, �� �������� ����� ������ � ����, ��� ��������� ����.";
			link.l1.go = "20";
		break;
		
		case "20":
			dialog.text = "��? ������, "+ GetFullName(Pchar)+", ���� � ���� ���� �����. ���� ����� ����� ����� ��������� �����: ''��� � ������, ��� � ������''. ��������, �� � ���� � �� ��� �������. ����� ����, ��� � ���� �� �������� �����?";
			link.l1 = "��, ����������, �� ������� ��� �����. ����� �����������.";
			link.l1.go = "21";
		break;
		
		case "21":
			dialog.text = "�����, "+ GetFullName(Pchar)+".";
			link.l1 = "� ���� �����.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("GothicDeliveryLuteroReadNotice");
		break;
		
		case "22":
			dialog.text = "��� �������! � � ��� �����������, ��� �� ��������. ������ ������� ��������� ���� ��������� ������. ��, ���� � ��� ������������, �� ���-�� ������ ���� ����.";
			link.l1 = "�� �� ��������� �����. ����� �����������, ������� ����� ���������.";
			link.l1.go = "23";
		break;
		
		case "23":
			dialog.text = "�� ������� ����� ����, �� �������. ������ � ���� ��� �� ��, ������ ��� �������� ����, ��������� �� �� ����. � ���� ����� ���� ������ ����� ����� �� ����. � ������... ������� ��������� ������. ������ ����� ��������-�����, �� �� �����.";
			link.l1 = "�����, ������, ��� ����. ������, ��� �� ������� ������� ���� ������. �� ���� ������.";
			link.l1.go = "24";
		break;
		
		case "24":
			dialog.text = "� �� ���� ����, "+ GetFullName(Pchar)+". � ����� ������, � ��� ��������� � ������, � �� �� ������ ��� ��� ��������. �� � ����� ������, ������� �� ��.";
			link.l1 = "���������, ������.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("GothicDeliveryLuteroCancelMoney");
		break;
		
		case "25":
			AddMoneyToCharacter(PChar, -200000);
			dialog.text = "��� �������, "+ GetFullName(Pchar)+", � �� � ��� ����� ��������� ���� ��������� ������.";
			link.l1 = "� ��������� ���, ���� ���������� � ������, ��� ����.";
			link.l1.go = "26";
		break;
		
		case "26":
			dialog.text = "�� �� ����, �� ����������. ������, "+ GetFullName(Pchar)+", �� ���� ������, ���� ���� ���-��� ��������. ��� ���� �� ������ ������� ���� ���������. ������ �� ����.";
			link.l1 = "��������� ������. ����, ��� �� ��� ������ � ���.";
			link.l1.go = "27";
		break;
		
		case "27":
			TakeNItems(PChar, "blade46", 1);
			dialog.text = "��, � ���� ������� �������. ���� ��� � �����. �������, ��� ���� ������� ��� ���� ���� �� ������ ��������� ���������, ������� �������-����������� ������� - �������� ���������.";
			link.l1 = "��� ���?";
			link.l1.go = "28";
		break;
		
		case "28":
			dialog.text = "��� �� ��� �� ������? ������� ��� ���, "+ GetFullName(Pchar)+", ���� ������� �������� ��� �� ���� ���.";
			link.l1 = "�������, ��� � ����. �����, ������, ������� �� ������.";
			link.l1.go = "29";
		break;
		
		case "29":
			dialog.text = "���� �������. ��, ������, "+ GetFullName(Pchar)+", �����, ��� �������� ���-������.";
			link.l1 = "����� � ��������. � ����� ������, �� �������.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("GothicDeliveryLuteroYesMoney");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
