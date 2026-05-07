# Studentų pažymių skaičiavimo sistema

## Diegimo ir paleidimo instrukcija (Unix / Makefile)

1. Sukompiliuoti programą:
```bash
make
```
2. Paleisti programą:
```bash
./main
```
3. Paleisti testus:
```bash
make test
./studentas_test
```
4. Sugeneruoti dokumentaciją:
```bash
make docs
```
5. Išvalyti kompiliacijos failus:
```bash
make clean
```

## Naudojimosi instrukcija

Programa siūlo interaktyvų meniu:
- **1** — Įvesti studentus rankiniu būdu
- **2** — Skaityti studentus iš failo
- **3** — Generuoti studentų failus (1k–10m įrašų)
- **4** — Rikiuoti ir skirstyti nuskaitytus failus (vector / list / deque)
- **5** — Išvesti rezultatus
- **0** — Baigti

Galutinis balas skaičiuojamas dviem būdais:
- Vidurkiu: `galutinis = ND_vidurkis × 0.4 + egzaminas × 0.6`
- Mediana: `galutinis = ND_mediana × 0.4 + egzaminas × 0.6`

---

RELEASES:

**v.pradinė**
- Padarytas base programos modelis
- Naudojami statiniai masyvai
- Rezultatas skaičiuojamas su mediana/vidurkiu

**v0.1**
- Galimybė generuoti pažymius
- Galimybė generuoti studentų vardus ir pavardes
- Dinaminės atminties masyvai/vektoriai
- Tvarkingesniė failų struktūra nei v.pradinė

**v0.2**
- Galimybe skaityti is failo
- Galimybe rikiuoti rezultatus
- Failo skaitymo laiko apskaiciavimas

**v0.3**
- Keli bug fixai
- Klaidų gaudymas jau buvo naudojamas nuo v0.1

**v0.4**
- Failu generavimas
- Ju isrusiavimas i 2 failus
- Visko laikas yra matuojamas

**v0.4.1**
- Sutaisytas rūšiavimo eiliškumas iš v0.4

**v1.0 pirma dalis**
- Galima atlikti testavimus su vector, list ir deque konteineriais
- Rezultatai pateikti README.md faile

------------
**Laikai**

Trumpai:
```
10000  - 0.0724s
100000 - 0.5376s
1000000 - 2.88213s
```

**v0.4 laikai (su 5 ND)**
```
1000      - 0.0083s
10000     - 0.0418s
100000    - 0.2258s
1000000   - 2.1877s
10000000  - 21.4033s
Visi      - 23.867s
```

Išsamiau:
```
1k  - nuskaitytas(0.00260862s) isrikiuotas(0.00305742s) isskirstytas(0.00118667s) maladiec isvesti(0.00508504s) vargsai isvesti(0.00288596s) visi rikiavimai(0.0174237s)
10k - nuskaitytas(0.0122946s)  isrikiuotas(0.027299s)   isskirstytas(0.00503313s) maladiec isvesti(0.0214935s) vargsai isvesti(0.0132335s) visi rikiavimai(0.0685688s)
100k- nuskaitytas(0.0674996s)  isrikiuotas(0.144965s)   isskirstytas(0.0221816s) maladiec isvesti(0.14138s)  vargsai isvesti(0.0945567s) visi rikiavimai(0.41721s)
1m  - nuskaitytas(0.480759s)   isrikiuotas(1.31925s)    isskirstytas(0.234185s) maladiec isvesti(1.4084s)   vargsai isvesti(1.0077s)  visi rikiavimai(3.98002s)
10m - nuskaitytas(4.58091s)    isrikiuotas(15.3626s)    isskirstytas(3.53852s) maladiec isvesti(15.0625s)  vargsai isvesti(10.1604s) visi rikiavimai(44.1762s)
```

<img width="624" height="119" alt="image" src="https://github.com/user-attachments/assets/ba2c4947-be74-4a2d-a7f7-18b27c404106" />
<img width="1068" height="720" alt="image" src="https://github.com/user-attachments/assets/22719650-be0b-4c0e-bdac-9ad62378d845" />

**v1.0 testavimas 1 dalis**

Sistema:
- Chip: Apple M2 (8 core GPU, 8 core GPU)
- OS: MacOS Tahoe 26.3.1 (a)
- RAM: 16GB unified memory
- SSD: 256GB

SVARBU: Rūšiavimas čia prilygsta `sort`, skirstymas yra studentų padalijimas į 2 konteinerius.

<img width="694" height="149" alt="image" src="https://github.com/user-attachments/assets/1f32b2eb-59e0-440e-9429-261ea6bf564a" />
<img width="674" height="156" alt="image" src="https://github.com/user-attachments/assets/7eb04200-f5ab-4c16-b7f6-22bd660ba879" />
<img width="692" height="151" alt="image" src="https://github.com/user-attachments/assets/32961796-ae0c-4f72-b068-22c1f122a5d1" />
<img width="360" height="218" alt="image" src="https://github.com/user-attachments/assets/34e5d3c0-9ed8-475f-9078-fdf690b1f8eb" />
<img width="405" height="218" alt="image" src="https://github.com/user-attachments/assets/4c0c1a7b-2933-46f5-b82f-b5b4f8461381" />
<img width="412" height="218" alt="image" src="https://github.com/user-attachments/assets/1b9ffd92-3681-4282-bd5a-25728a6a52dc" />

**v1.0 testavimas 2 dalis**

1 strategijos sparta pateikta 1 dalyje.

2 strategija (tik vargšiukų ir studentų konteineriai):
Pažiūrėjus į rezultatus naudojant 2 strategiją matomas programos paspartėjimas skirstant studentus į konteinerius. Vektoriai pagreitėjo iki 49%, list ir deque 30-35%.

<img width="704" height="147" alt="image" src="https://github.com/user-attachments/assets/5ed05de1-246a-4111-91d0-3ec143cebe79" />
<img width="678" height="147" alt="image" src="https://github.com/user-attachments/assets/a80db1a2-7ad8-46fe-a10f-d9d89bdc32f4" />
<img width="698" height="147" alt="image" src="https://github.com/user-attachments/assets/21d19c98-d104-4384-9542-13c217247b9b" />
<img width="362" height="226" alt="image" src="https://github.com/user-attachments/assets/eaa4c2f9-be7e-4b25-a86b-3efd672ab4c5" />
<img width="361" height="226" alt="image" src="https://github.com/user-attachments/assets/a30a3c82-8796-4a14-96f3-b4625c4a692f" />
<img width="362" height="226" alt="image" src="https://github.com/user-attachments/assets/60ecd561-3f71-435d-95d9-31d9091a0523" />

**v1.0 testavimas 3 dalis**

3 strategija:
Skirstymas daromas su `partition` funkcija.
Matome, kad skirstymo greitis paspartėjo, nors ir labai minimaliai.

<img width="658" height="141" alt="image" src="https://github.com/user-attachments/assets/a4a8ddf8-6523-4733-8142-694e024c2a45" />
<img width="361" height="217" alt="image" src="https://github.com/user-attachments/assets/64be7f4d-a48d-4246-9cc3-1da12e849cf6" />

**v1.1**

- `Studentas` realizacija perkelta iš `struct` į `class`
- Atlikta `struct` ir `class` versijų palyginamoji analizė
- Atlikta eksperimentinė analizė su kompiliatoriaus optimizavimo flag'ais `-O1`, `-O2` ir `-O3`

**Struct ir Class palyginimas**
!Viskas atlikta su vector!

| Įrašų skaičius | Struct (s) | Class (s) |
|---|---:|---:|
| 100000 | 0.3591149 | 0.380284 |
| 1000000 | 3.102802 | 3.04553 |

**Optimizavimo flag'ų analizė**

| Versija | Flag | Laikas (s) | `main` dydis |
|---|---|---:|---:|
| Struct | `-O1` | 3.191659 | 345KB |
| Struct | `-O2` | 3.101894 | 296KB |
| Struct | `-O3` | 3.085912 | 296KB |
| Class | `-O1` | 3.29307 | 314KB |
| Class | `-O2` | 3.30363 | 314KB |
| Class | `-O3` | 3.2684 | 329KB |

Iš pateiktų rezultatų matyti, kad `Struct` ir `Class` versijų sparta skiriasi nedaug. `Struct` versija kai kuriais atvejais buvo šiek tiek greitesnė, tačiau skirtumas nėra didelis. Taip pat matyti, kad geriausi matuoti rezultatai gauti naudojant `-O3` optimizavimo lygį, o vykdomojo failo dydis priklausomai nuo optimizavimo flag'o ir realizacijos šiek tiek kito.

**v1.2**

- `Studentas` klasė perkelta į atskirus failus `Studentas.h` ir `Studentas.cpp`
- Realizuota pilna `Rule of Five`
- Perdengti įvesties ir išvesties operatoriai `operator>>` ir `operator<<`
- Parašytas atskiras testų failas `studentas_test.cpp`
- Testai kompiliuojami ir paleidžiami naudojant `make test` ir `./studentas_test`

**Rule of Five ir operatorių lentelė**

| Metodas | Paskirtis |
|---|---|
| `Studentas()` | Sukuria tuščią `Studentas` objektą |
| `Studentas(const std::string&, const std::string&)` | Sukuria studentą su vardu ir pavarde |
| `Studentas(const Studentas&)` | Kopijavimo konstruktorius |
| `Studentas& operator=(const Studentas&)` | Kopijavimo priskyrimo operatorius |
| `Studentas(Studentas&&) noexcept` | Perkėlimo konstruktorius |
| `Studentas& operator=(Studentas&&) noexcept` | Perkėlimo priskyrimo operatorius |
| `~Studentas()` | Destruktorius |
| `std::istream& operator>>(std::istream&, Studentas&)` | Įveda vieno studento duomenis į objektą |
| `std::ostream& operator<<(std::ostream&, const Studentas&)` | Išveda vieno studento duomenis į srautą |

**Įvesties ir išvesties paaiškinimas**

- Rankinė įvestis programoje atliekama per meniu, kai vartotojas pats įveda vardą, pavardę, namų darbų pažymius ir egzamino balą.
- Automatinė įvestis programoje atliekama sugeneruojant pažymius arba sugeneruojant visus studento duomenis atsitiktinai.
- Įvestis iš failo atliekama nuskaitant `.txt` failą su studentų duomenimis.
- Išvestis į ekraną atliekama naudojant `std::cout`.
- Išvestis į failą atliekama naudojant `std::ofstream`.
- Perdengtas `operator>>` leidžia nuskaityti vieną `Studentas` objektą iš srauto formatu: `vardas pavarde nd1 nd2 ... egz`.
- Perdengtas `operator<<` leidžia išvesti vieno `Studentas` objekto informaciją į bet kurį išvesties srautą.

**Testų lentelė**

| Testas | Kas tikrinama | Rezultatas |
|---|---|---|
| `testDefaultConstructor` | Default konstruktorius | Pavyko |
| `testParameterizedConstructor` | Konstruktorius su parametrais | Pavyko |
| `testCopyConstructor` | Kopijavimo konstruktorius | Pavyko |
| `testCopyAssignment` | Kopijavimo priskyrimo operatorius | Pavyko |
| `testMoveConstructor` | Move konstruktorius | Pavyko |
| `testMoveAssignment` | Move priskyrimo operatorius | Pavyko |
| `testInputOperator` | `operator>>` veikimas | Pavyko |
| `testOutputOperator` | `operator<<` veikimas | Pavyko |
| `testGradeCalculation` | Galutinio balo skaičiavimas | Pavyko |

**Kaip paleisti testus**

```bash
make test
./studentas_test
```

Tikėtinas rezultatas:

```text
Visi Studentas testai pavyko.
```

**įrodymas**

![alt text](image.png)


**Išvada**

`v1.2` versijoje `Studentas` klasė buvo praplėsta taip, kad atitiktų `Rule of Five` reikalavimus ir palaikytų darbą su srautais per perdengtus `operator>>` ir `operator<<`. Visi realizuoti metodai buvo patikrinti atskirame testų faile, o testų rezultatai parodė, kad konstruktoriai, kopijavimo ir perkėlimo operacijos bei įvesties ir išvesties operatoriai veikia korektiškai.

**v1.5**

- Sukurta abstrakti bazinė klasė `Zmogus`
- `Studentas` klasė pakeista į išvestinę klasę iš `Zmogus`
- Išlaikytas `v1.2` funkcionalumas: `Rule of Five`, `operator>>`, `operator<<` ir esami testai
- Papildyti testai, kad būtų patikrintas abstraktumas ir paveldėjimas

**Klasių struktūra**

| Klasė | Tipas | Atsakomybė |
|---|---|---|
| `Zmogus` | Abstrakti bazinė klasė | Saugo bendrus žmogaus duomenis: `vardas_`, `pavarde_` |
| `Studentas` | Išvestinė klasė | Saugo studento pažymius, egzamino balą ir galutinius rezultatus |

**Kodėl `Zmogus` yra abstrakti**

- `Zmogus` klasėje realizuotas grynai virtualus metodas `tipas() const = 0;`
- Dėl to negalima kurti `Zmogus` objektų tiesiogiai
- Galima kurti tik iš jos išvestinių klasių objektus, pvz. `Studentas`

**Paveldėjimo ir metodų lentelė**

| Elementas | Realizacija |
|---|---|
| Bazinė klasė | `class Zmogus` |
| Abstraktumas | `virtual std::string tipas() const = 0;` |
| Išvestinė klasė | `class Studentas : public Zmogus` |
| Bendra žmogaus informacija | `vardas_`, `pavarde_` laikomi `Zmogus` klasėje |
| Specifinė studento informacija | `nd_`, `egz_`, `galutinis_vid_`, `galutinis_med_` laikomi `Studentas` klasėje |
| Polimorfizmas | `Studentas` realizuoja `tipas()` ir gali būti naudojamas per `Zmogus*` |

**Testų lentelė**

| Testas | Kas tikrinama | Rezultatas |
|---|---|---|
| `testAbstractBaseClass` | `Zmogus` yra abstrakti klasė | Pavyko |
| `testPolymorphicUsage` | `Studentas` naudojimas per `Zmogus*` | Pavyko |
| `testDefaultConstructor` | Default konstruktorius | Pavyko |
| `testParameterizedConstructor` | Konstruktorius su parametrais | Pavyko |
| `testCopyConstructor` | Kopijavimo konstruktorius | Pavyko |
| `testCopyAssignment` | Kopijavimo priskyrimo operatorius | Pavyko |
| `testMoveConstructor` | Move konstruktorius | Pavyko |
| `testMoveAssignment` | Move priskyrimo operatorius | Pavyko |
| `testInputOperator` | `operator>>` veikimas | Pavyko |
| `testOutputOperator` | `operator<<` veikimas | Pavyko |
| `testGradeCalculation` | Galutinio balo skaičiavimas | Pavyko |

**Kaip paleisti testus**

```bash
make test
./studentas_test
```

Tikėtinas rezultatas:

```text
Visi Studentas ir Zmogus testai pavyko.
```

**Kaip demonstruojamas abstraktumas**

- Testuose naudojamas `static_assert(std::is_abstract<Zmogus>::value)`, kuris patvirtina, kad `Zmogus` yra abstrakti klasė.
- Testuose taip pat naudojamas `static_assert(std::is_base_of<Zmogus, Studentas>::value)`, kuris patvirtina, kad `Studentas` paveldi iš `Zmogus`.
- Papildomai patikrinama, kad `Studentas` objektas gali būti pasiekiamas per `Zmogus*`.

**Programos logikos suderinamumas su v1.2**

- Programos veikimo logika išliko tokia pati kaip `v1.2` versijoje.
- Rankinė įvestis, automatinis generavimas, skaitymas iš failo, išvedimas į ekraną ir išvedimas į failą veikia kaip ir anksčiau.
- `Studentas` klasė išlaikė `Rule of Five` ir srautų operatorių realizaciją, todėl ankstesni testai liko pritaikomi ir po paveldėjimo įvedimo.

**Įrodymas**


<img width="675" height="87" alt="image" src="https://github.com/user-attachments/assets/f927f2fc-42d7-4b35-a6b5-06b0967702ec" />


**Išvada**

`v1.5` versijoje buvo įvesta paveldėjimo hierarchija, kurioje `Zmogus` yra abstrakti bazinė klasė, o `Studentas` yra iš jos išvesta klasė. Tokiu būdu bendri žmogaus duomenys buvo perkelti į bazinę klasę, o visa studentui specifinė logika liko `Studentas` klasėje. Visi `v1.2` metodai ir testai išliko veikiantys, papildomai buvo pademonstruotas abstraktumas ir polimorfinis naudojimas.

---

**v2.0**

- Testai perkelti į [Catch2](https://github.com/catchorg/Catch2) (v2.13.10) unit testų framework'ą
- Visos klasės aprašytos Doxygen komentarais
- Sugeneruota HTML ir LaTeX/PDF dokumentacija (katalogas `docs/`)
- Atnaujintas `Makefile`: pridėtas `make docs` taikinys
- Atnaujintas `.gitignore`: pašalinti visi sugeneruoti ir binariniai failai

**Catch2 testų lentelė (v2.0)**

| Testas | Kas tikrinama | Kategorija |
|---|---|---|
| Numatytasis konstruktorius | Visi laukai tuščia/nuliniai | `rule_of_five` |
| Konstruktorius su parametrais | Vardas ir pavardė priskirti | `rule_of_five` |
| Kopijavimo konstruktorius | Visi laukai nukopijuoti | `rule_of_five` |
| Kopijavimo priskyrimo operatorius | Visi laukai nukopijuoti | `rule_of_five` |
| Perkėlimo konstruktorius | Duomenys perkelti | `rule_of_five` |
| Perkėlimo priskyrimo operatorius | Duomenys perkelti, šaltinis tuščias | `rule_of_five` |
| `operator>>` | Skaito vardą, pavardę, ND, egz | `operators` |
| `operator<<` | Išveda teisingą formatą | `operators` |
| Galutinio balo skaičiavimas | Vidurkis ir mediana teisingi | `grades` |
| Zmogus abstrakti klasė | `static_assert` patikrinimai | `inheritance` |
| Polimorfinis naudojimas | Prieiga per `Zmogus*` | `inheritance` |

**Kaip paleisti testus**

```bash
make test
./studentas_test
```

Tikėtinas rezultatas:

```text
Passed all 11 test cases with 56 assertions.
```

**Dokumentacija**

Dokumentacija sugeneruota naudojant Doxygen 1.17.0. Katalogas `docs/` turi:
- `docs/html/` — naršyklėje atidaromas `index.html`
- `docs/latex/` — LaTeX šaltinis ir sukompiliuotas `refman.pdf`

```bash
# Atidarti HTML dokumentaciją
open docs/html/index.html

# Perkompiliuoti PDF (reikalingas TeX)
cd docs/latex && make
```

**Išvada**

`v2.0` versijoje testai perkelti į Catch2 framework'ą, kuris suteikia aiškesnę testų struktūrą su `TEST_CASE` ir `REQUIRE` makro komandomis. Sugeneruota pilna Doxygen dokumentacija HTML ir LaTeX formatais. Repozitorija sutvarkyta: `.gitignore` atnaujintas, pašalinti visi nereikalingi failai (ideti i gitignore).
