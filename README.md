# build69-gtasa2.0
SA-MP ANDROID build 69 to GTASA 2.0 with AML
![msg6385958517-43711](https://github.com/tendensy/build69-gtasa2.0-remake/assets/130832390/8d4f8c81-06d6-42a1-9847-c1758c7889df)


# ChangeLog

# 15.09.2023
**SUPPORT JAVA (60% work)**
- Добавлена поддержка Java классов
- InitSAMP (50%)
- CJava* pJava class

# 21.07.2023
- Новый gui.cpp (Кнопки ALT и Render Version)
- Новый текст при запуске в netgame.cpp

# 21.07.23
- Новый дизайн для кнопок
- Debug в левом нижнем углу (FPS, POS, MEM и т.д)
- Отдельный файл для хуков (перенос с 1.08)
- CTimerPause_hook (Отслеживание входа в паузу)
- Отслеживание команд в CNetGame::SendChatCommand()
- Команды /q и /recconect
- CRadar__SetCoordBlip_hook (Отслеживание места координат и дальнейший
                                                                             телепорт через RPC в a_samp)
- CTimerResume_hook (Отслеживание выхода из паузы)

# 22.07.23
- Добавлены CrashFixPatches связанные с CPools::ms_pEntryInfoNodePool
- Добавлены SCAndPatches (отключение заставки Social Club
                                                           aka. нажать "OFFLINE" чтобы продолжить)
- Копия ImGui от BLACK RUSSIA
- Перенесен CFPSFix::Routine()
- CFirstPerson (первое лицо)
- Обновление CPlayerPed::ProcessAttachedObjects() (отслеживание RwAnim)
- Обновление CPlayerPed (MATRIX4X4* RwMatrixMultiplyByVector(VECTOR* out, MATRIX4X4* a2, VECTOR* in))
- Фикс обводки чата
- CCam__Process_hook (отслеживание камеры)
- CLoadingScreen_DisplayPCScreen_hook (экран загрузки (loadingscreen, splashscreen))
- Patch for IMG Count (максимальное количество img архивов (max count of img archives))
- Debug в оффлайн режиме игры (FPS, POS, MEM и т.д)

# 23.07.23
- Фикс рандомного краша при работе с текстурами
- Остановка загрузки tracks2.dat & tracks4.dat (FIX ME)
- Фикс рандомного краша из-за RW

# 28.07.23
- Hook на LoadingScreenPC

# 05.08.23
- Перенесен хук на перенос путя игры (0/WeiktonGames) (OFF)
- Перенос шрифта в логичный путь (arial_bold)

# Connection (EN/RU)
- **Сonnect / Подключение**
**[RU]**
- менять айпи в main.h
- ник в main.cpp
#
**[EN]**
- change IP in main.h file
- change your nickname in main.cpp
#
- **StartUp / Запуск**
- Перенести все файлы с названием  (они где то в дата)"tracks" в SAMP/
- Добавляем шрифт arial_bold.ttf в папку SAMP/fonts

