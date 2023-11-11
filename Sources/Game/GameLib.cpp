extern void __RegisterClass__GameManager();
extern void __RegisterClass__GameMenu();
extern void __RegisterClass__CheckMatchesGamefieldBehaviour();
extern void __RegisterClass__ChipsFallGamefieldBehaviour();
extern void __RegisterClass__ChipSpawner();
extern void __RegisterClass__Cell();
extern void __RegisterClass__CellBehaviour();
extern void __RegisterClass__Chip();
extern void __RegisterClass__ChipBehaviour();
extern void __RegisterClass__Gamefield();
extern void __RegisterClass__GamefieldBehaviour();


extern void InitializeTypesGameLib()
{
    __RegisterClass__GameManager();
    __RegisterClass__GameMenu();
    __RegisterClass__CheckMatchesGamefieldBehaviour();
    __RegisterClass__ChipsFallGamefieldBehaviour();
    __RegisterClass__ChipSpawner();
    __RegisterClass__Cell();
    __RegisterClass__CellBehaviour();
    __RegisterClass__Chip();
    __RegisterClass__ChipBehaviour();
    __RegisterClass__Gamefield();
    __RegisterClass__GamefieldBehaviour();
}