all:
	@echo Building decrypted EBOOT.PBP
	@make -C app
	@mv app/EBOOT.PBP app/EBOOT_DEC.PBP
	@echo Building encrypted EBOOT.PBP
	@python3 app/resource/psptools/pack_ms_game.py --vanity themadump app/EBOOT_DEC.PBP app/EBOOT_ENC.PBP>/dev/null
	@rm -rf app/PSP
	@mkdir -p app/PSP/GAME/themadump
	@cp app/EBOOT_ENC.PBP app/PSP/GAME/themadump/EBOOT.PBP
	@cd app && zip -r themeadump.zip PSP && cd ..

clean:
	make -C app clean
	@rm -rf app/PSP app/EBOOT* app/*.zip
