[97mquest The Crystal Cavern begin
	state start begin
		when login or levelup with pc.get_level() >= 1 begin
			send_letter("The Crystal Cavern")
		end
		when button or info begin
			say_title("PvP Mission")
			say("Welcome Good day " .. pc.get_name() << ",")
			say("I see you are weak & need some training.")
			say("No problem at all i will help you")
			say("on the path to becoming a great warrior!")
			wait()
			say_title("The Crystal Cavern")
			say("Defeat a total of 14 metins")
			say("[ENTER]Of course, I will reward you as well!")
			set_state(pvpquest1)
		end
	end
	state pvpquest1 begin
		when letter begin
			send_letter("Mission to greatness")
		end
		when button or info begin
			say_title("Your First Mission")
			say("Destroy a total of 14 metins ")
			say()
			say_reward("You have killed " .. pc.getqf("kills") << " out of 14.")
			wait()
			send_letter("Your First Mission")
		end
		when kill with 1 begin
			pc.setqf("kills", pc.getqf("kills") + 1)
			if pc.getqf("kills") >= 14 then
				pc.delqf("kills")
				notice_all(pc.get_name() .. " has completed the first mission!")
				say_title("You have successfully completed the first mission")
				affect.add_collect(apply.APPLY_DEX, 2, 60 * 60 * 24 * 365 * 10)
				say("[ENTER]You receive:")
				say_reward("+50HP Permanent.")
				say_reward("+2Defense Permanent")
				pc.delqf("kills")
				set_state(__COMPLETE__)
				if pc.is_gm() then
					pc.setqf("daily_quest", get_time() + 10)
				else
					pc.setqf("daily_quest", get_time() + 24 * 60 * 60)
				end
				restart_quest()
			else
				clear_letter()
			end
		end
	end
	state __COMPLETE__ begin
	end
end
[0m