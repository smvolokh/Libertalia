void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;
	string NPC_Meeting;	
	int Shit, i;
	ref refStore;
	ref sld;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
        case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

        case "First time":
				PlaySound("VOICE\Russian\GOTHIC\GG_HALLO_M\GG_HALLO_M_" + rand(15) + ".wav");
			Diag.TempNode = "first time";
			if(CheckAttribute(PChar, "quest.Contraband.active"))
			{
				int iTmp = false;
				int iChIdx;

				// ����� ���.  �� �������� ������
				for (i=0; i<COMPANION_MAX; i++)
				{
					iChIdx = GetCompanionIndex(GetMainCharacter(), i);
					if (iChIdx>=0)
					{
						sld = GetCharacter(iChIdx);
            			if (GetCharacterShipClass(sld) < ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5))
						// --> CheatSurfMenu by Cheatsurfer
						{
							if (!CheckAttribute(pchar, "CSM.FreeSmuggling"))
							{
								iTmp = true;
							}
						}
						// CheatSurfMenu by Cheatsurfer <--
					}
				}
				
				if (iTmp)
				{
					dialog.text = NPCStringReactionRepeat("���� ���, �� ��������, ����� �� �� �����"+ GetSexPhrase("��","���") +" �� ����� ��������� ������? �� �� ��� ������� ��������� � ����� ���������"+ GetSexPhrase("","�") +". ���������� � ������� �� ������� �������.", 
						"�"+ GetSexPhrase("��","��") +" �� �� ������. � �� ���� ���� ������� ������.", 
						"�����-�����, ������ � ������ � ��������.",
						"��� �� �� ���� ������"+ GetSexPhrase("","a") +"...", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("������-������, ���"+ GetSexPhrase("��","��") +" �������� ������.", 
						"�� �����, � ����� - ���� ���� ���, ������ ���.",
						"��-�, �� ������� ��������...", 
						"��, � �������"+ GetSexPhrase("��","��") +"!", npchar, Dialog.CurrentNode);
						link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
					break;
				}
			
				Dialog.snd = "voice\SMSH\SMSH001";
				dialog.Text = RandPhraseSimple("��, ��� �� ��� �����"+ GetSexPhrase("","�") +", "+ GetSexPhrase("��������","�������") +"?",
                                          RandSwear() + "��� ���� ��� �����?!");
				Link.l1 = "����������, ������, ����� �������� �����!";
				Pchar.quest.Contraband.Counter = 0; // �� ���������
				if(Pchar.Location == Pchar.location.from_sea)
				{
					Link.l1.go = "Exchange";
				}
				else
				{
					Link.l1.go = "No_Ship";
				}
				//�� ������� �����������, ����������� ������, ������ ��� �����.
				if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))				
				{
					Link.l2 = "� ����� �� ������������ ����������� " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen") + "! ���������� ��� ������� ������ � ��������� �� ���� - �� ����������!";
					Link.l2.go = "GenQuestKillContraband_1";
				}
			}
			else
			{
//================ METRO ====================
				//���� ��������, �� �������������, ����� ��������
				if (CheckAttribute(PChar, "GenQuest.contraTravel.payed") && sti(PChar.GenQuest.contraTravel.payed) == true)
				{
                    dialog.Text = RandPhraseSimple("���, �������-��!!! ��� � ��, � �� �� �� ��������� ������. ����, �� ����������.", "�������������, ��� ������� �������. ����� ������� �������� ������!");
					//�� ������� �����������, ����������� ������, ������ ��� �����.
					if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))
					{
						Link.l1 = "� ����� �� ������������ ����������� " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen") + "! ���������� ��� ������� ������ � ��������� �� ���� - �� ����������!";
						Link.l1.go = "GenQuestKillContraband_1";
						break;
					}
					//���� ������ ����������, � ���..
					if (GetPassengersQuantity(PChar) > 0)
					{
						dialog.Text = "� �� ��� �����? �� �������������� ��������� ������ ���������, � �� �����.";
						Link.l1 = "���...";
						Link.l1.go = "Exit";
						break;
					}
					//���� ������ ����������� ��� ����� ������� ���� ��� :), � ���..
					if (GetCompanionQuantity(PChar) > 1 || sti(PChar.ship.type) != SHIP_NOTUSED)
					{
						dialog.Text = RandPhraseSimple("�� ���? �� �������������� ��������� ���������, � �� ��������.", "����������! ���� �� ���������� �� ������ �������, �� �������.");
						Link.l1 = "��, ����...";
						Link.l1.go = "Exit";
						break;
					}
					//���� ����� ��������, ���� ������... 
					if (CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight") && sti(PChar.GenQuest.contraTravel.PatrolFight) == true)
					{
						if (chrDisableReloadToLocation) // ��� ��� ����
						{
						    dialog.Text = "�������! �� ���� �� �����, �� ��� �� ������.";
							Link.l1 = "�� ��...";
							Link.l1.go = "Exit";
							break;
						}
						dialog.Text = RandPhraseSimple("������� �� ������. �� �� ������� �����. ������������.", "�������! ������� ������"+ GetSexPhrase("��","���") +". ����.");
						ChangeContrabandRelation(PChar, 5);
						PChar.GenQuest.contraTravel.PatrolFight = false;
						AddCharacterExpToSkill(Pchar, "Sneak", 50);
					}
					//��� ��� ��, ������������.
					Link.l2 = "��� ���.";
					Link.l2.go = "Exit";
					//� ��� �������... 
					if (GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) < frandSmall(13.0*(1.0 - pow(0.9, sti(PChar.rank)))) && !CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight"))
					{
						AddDialogExitQuest("Rand_ContrabandInterruption");
						PChar.GenQuest.contraTravel.PatrolFight = true;
					}
					else 
					{
						//�������� ���� � �������.
						refStore = CharacterFromID("Abracham_Gray");
						ChangeCharacterAddressGroup(refStore, "Ship_deck", "goto", "goto2");
						refStore.dialog.Filename = "Smuggler_Ship_dialog.c";
                        refStore.dialog.CurrentNode = "Travel_talkStart";
						//������, ����� RemoveTravelSmugglers ������� ��� �����
						PChar.GenQuest.contraTravel.ship = true;
						PChar.quest.Munity = "";  // ������� ������ � ������
						
						SetLaunchFrameFormParam("������ " + sti(Pchar.GenQuest.contraTravel.destination.days) + " ����." + NewStr() + "������ ������� ���������������.",
						                        "Reload_To_Location", 0.1, 5.0);
                        bQuestCheckProcessFreeze = true;
						WaitDate("", 0, 0, sti(Pchar.GenQuest.contraTravel.destination.days), rand(20), 0);
						bQuestCheckProcessFreeze = false;
						MakeCloneShipDeck(refStore, true); // ������� ������
						SetLaunchFrameReloadLocationParam("Ship_deck", "reload", "reload1", "Travel_talkOnDeck");
						AddDialogExitQuest("LaunchFrameForm");
						AddCharacterExpToSkill(Pchar, "Sneak", 50);
					}
//================ METRO ====================
				}
				else
				{
                    // ���� ������� ��� �����
					if (CheckAttribute(NPChar, "ContrabandInterruption"))
					{
					    dialog.Text = RandSwear()+ "�������! �� ���� �� �����, �� ��� �� ������!";
						Link.l1 = "�����!";
						Link.l1.go = "Exit";
					}
					else
					{
						dialog.Text = "������, ���������� ������! ������� ������ - �� �������� ���� �����!";
						Link.l1 = RandPhraseSimple("�� ������ ��� ��������, ������?", "�� ���������� ������ �������, �������!");
						Link.l1.go = "Exit_fight";
						Link.l2 = "�� �����, � ����, ��� ����� ������. �� �������.";
						Link.l2.go = "Exit";
					}
				}
			}
		break;

		case "No_Ship":
			Dialog.snd = "voice\SMSH\SMSH003";
			dialog.Text = "�� ����� �����, ��� ��? ��� ���� �������?";
			Link.l1 = RandPhraseSimple("������� � �����"+ GetSexPhrase("","�") +" ���������, ��� ����� ��� �������� �������.", "�� �����"+ GetSexPhrase("","�") +" ��������� ��������. ����������� ������� ��������� �� ��� ������ �������.");
			Link.l1.go = "No_ship_1";
			Link.l2 = "������ ����������!";
			Link.l2.go = "Cancellation";
		break;

		case "No_ship_1":
			Dialog.snd = "voice\SMSH\SMSH004";
			dialog.Text = "�� ���� �������, � ������� �� �����. ��������� ���� �������, ������ ���������� - ����� �� ���� �� �������� ��������� �������.";
			Link.l1 = "������. ����� ���� �����.";
			Link.l1.go = "Exit";
		break;

		case "Cancellation":
            if (sti(Pchar.quest.Contraband.Counter) == 0)
            {
    			dialog.Text = "����������? �� ���, ��������?";
    			Link.l1 = "���������� ��������.";
    			Link.l1.go = "Cancellation_1";
			}
			else
            {
    			dialog.Text = "�� � �����. �� � ��� ������� �����������.";
    			Link.l1 = "�����!";
    			Link.l1.go = "Finish_exit";
			}
		break;

		case "Cancellation_1":
			if( makeint(Pchar.rank) <= 3 || GetSummonSkillFromNameToOld(Pchar, SKILL_FENCING) <= 5 || GetSummonSkillFromNameToOld(Pchar, SKILL_LEADERSHIP) <= 5 )
			{
				if(Rand(1) == 1)
				{
					ChangeContrabandRelation(pchar, -30);
					Dialog.snd = "voice\SMSH\SMSH006";
					dialog.Text = "������"+ GetSexPhrase("��","��") +"! �� �� ������ ��� ��� ��������! ����������� �� ��� ����� �������!";
					Link.l1 = "� ��� ��� ���� ��!";
					Link.l1.go = "Exit_fight";			
				}
				else
				{
					ChangeContrabandRelation(pchar, -10);
					Dialog.snd = "voice\SMSH\SMSH007";
					dialog.Text = "��� �� ������ ���� � ���!";
					Link.l1 = "������������� ������� ����-������ ���, ���!";
					Link.l1.go = "Exit_cancel";
				}
			}	
			else
			{
				ChangeContrabandRelation(pchar, -10);
				Dialog.snd = "voice\SMSH\SMSH008";
				dialog.Text = "�� �� ���� ��� ���������!";
				Link.l1 = "��-��!";
				Link.l1.go = "Exit_cancel";			
			}	
		break;

		case "GenQuestKillContraband_1":
			//������� ������� �� "�����"...
			if(CheckAttribute(PChar, "GenQuest.contraTravel.active") && sti(PChar.GenQuest.contraTravel.active) == true)
			{
				Statistic_AddValue(PChar, "contr_TravelKill", 1);
				ChangeContrabandRelation(pchar, -20); //���� ������ ����
			}
			dialog.Text = "�� ��� ������ �������� �� ����� ��������!";
			Link.l1 = "����� �� ��� ������. � ���� ������ ������ - � ������ ������������� ����� �� �����!";
			Link.l1.go = "Exit_fight";
		break;
		
		case "Exit_Cancel":
            DeleteAttribute(Pchar, "quest.Contraband");
            CloseQuestHeader("Gen_Contraband");
			Pchar.quest.Rand_Smuggling.over = "yes";
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		break;
		
		case "Exit_fight":
            DeleteAttribute(Pchar, "quest.Contraband.active");
			DeleteAttribute(Pchar, "quest.Contraband.counter");			

			AddSimpleRumourCity("�������? ������� � ����� ������� ������ �� ��������������� �������. � ��� �� �� ������? ��������, ������� ������� ��������� ����� ��������, ������� ����! " +
				"����� ������ � ���� � ������� ��������� - ���� ���������� ����� ��������. � ���� �������, ��� � ���� ������. ��� � ����� ������, ����� ������, � �� ����� - �� ������, �� �������, �� ����� ���������������. ��� �� ��� � ���� ����������� ��������-�� �����������!", Pchar.quest.contraband.City, 3, 5, "");	

			CloseQuestHeader("Gen_Contraband");
			Pchar.quest.Rand_Smuggling.over = "yes";
			LAi_group_FightGroups(LAI_GROUP_PLAYER, pchar.GenQuest.Smugglers_Group, true);
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
			LAi_SetFightMode(Pchar, true);

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

		case "Finish_exit":
            // ������� �� ����
            if(GetSummonSkillFromName(pchar, "Sneak") < Rand(120))
			{
				AddDialogExitQuest("Rand_ContrabandInterruption");
				for (i=1; i<=3; i++)
				{
					characters[GetCharacterIndex("Rand_Smug0"+i)].ContrabandInterruption = true;
				}
			}
	AddCharacterExpToSkill(PChar, "Leadership", 200); 
	AddCharacterExpToSkill(PChar, "Sneak", 200); 
	AddCharacterExpToSkill(PChar, "Commerce", 200); 
	AddCharacterExpToSkill(PChar, "Fortune", 200); 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			ChangeContrabandRelation(pchar, 15);
            OfficersReaction("bad");
            ChangeCharacterComplexReputation(pchar,"nobility", -1);
            
            CloseQuestHeader("Gen_Contraband");
            
			DeleteAttribute(Pchar, "quest.Contraband.active");
			DeleteAttribute(Pchar, "quest.Contraband.counter");
	
			Pchar.quest.Rand_Smuggling.over = "yes";
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
		break;

		case "Exchange":
			// ���� �������� -->
            if(FindContrabandGoods(Pchar) == -1 && sti(Pchar.quest.Contraband.Counter) == 0)
            {
				dialog.Text = "��, � ���� �� ����� �������? � ���� �� ������ ���, ��� ����� �������! ���, ��� ����� � ���� � �����, ����� ������ � ������!";
				Link.l1 = "�� �������.";
				Link.l1.go = "NoGoods";
			}
			else
			{
                // ��������� ��������� -->
                if (sti(Pchar.quest.Contraband.Counter) == 0) // �� ��������� ���
                {
                    if(drand(11) == 3)
                    {
        				dialog.Text = "���-���... �������, �� ������� ���� ����� ���������. ���� �� �� �������� ���������� �������.";
        				Link.l1 = "��� �, ����������!";
        				Link.l1.go = "Exit_fight";
                        break;
        			}
        			// ���� � ������� �� ���� ����������!!!
        			if(GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) < Rand(12))
        			{
                        SetCoastalGuardPursuit();
        			}
        			// ��� �������� �� ������� �� ����� - ������� ����
        			SetTimerCondition("Rand_ContrabandInterruptionAtSeaEnded", 0, 0, 60, false);// ���� � ����� �����, ����, �� 2 ����
        			
                    Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition.l1 = "MapEnter";
        			Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition = "Rand_ContrabandAtSeaEnded";
    			}
    			// ��������� ��������� <--
				dialog.text = "����, ����� ��������� ������.";										  
				Link.l1 = "�� ����� ���������.";
				Link.l1.go = "Exchange1"; 
				if (sti(Pchar.quest.Contraband.Counter) == 0)
    			{
        			Link.l99 = "�������, � ���������"+ GetSexPhrase("","�") +".";
    				Link.l99.go = "Cancellation";
				}				
            }
		break;
		
		case "Exchange1":
			NPChar.quest.meeting = NPC_Meeting;
			Diag.CurrentNode = Diag.TempNode;		 
			DialogExit();
			
			LaunchContrabandTrade(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId),  sti(pchar.FindContrabandGoods.StoreIdx));	
		break;				
	}
}