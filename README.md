Prezentacja na drugi etap Olimpiady Informatycznej
==================================================

Instalacja
==========

Należy zainstalować Qt 4.8 http://qt-project.org/downloads
Projekt kompiluje się przy pomocy programu cmake, wykonując następujące polecenia:
* Stworzenie katalogu przechowującego pliki kompilacji i plik wykonywalny:

  mkdir build

	cd build

* Wygenerowanie plików Makefile przy pomocy programu cmake:

	cmake ../

* Kompilacja::

	make

Wówczas w katalogu build/bin/ powinien pojawić się plik wykonywalny, który można przenieść w dowolne miejsce -- nie jest sztywno związany z żadnymi dodatkowymi plikami.


Używanie prezentacji
====================

Prezentację można przełączać między dwoma trybami: ``Prezentacja`` i ``Edytor``.

**Prezentacja**

W tym trybie można oglądać prezentację.
Należy ją rozpocząć poprzez wykonanie dowolnego kroku do przodu.
Prezentacja przewija się automatycznie, ale można ją w każdym momencie zastopować.
Podczas oglądania komentarzy możliwe jest ich przewijanie (przy pomocy myszy), gdyby nie mieściły się na ekranie.

W trakcie prezentacji można ręcznie robić następujące skoki:
* Następny krok (strzałka w prawo) -- przenosi do kolejnej akcji, którą można wykonać (np. pokazanie kolejnego testu, albo przejście do kolejnego zadania, jeśli wszystkie testy zostały już pokazane).
* Poprzedni krok (strzałka w lewo) -- operacja odwrotna do Następnego kroku.
* Następne zadanie (klawisz K) -- przenosi do kolejnego zadania z aktualnego raportu, pomijając jeszcze nie pokazane testy w aktualnym zadaniu.
* Poprzednie zadanie (klawisz J) -- operacja odwrotna do Następnego zadania.
* Następny raport (klawisz L) -- przenosi do kolejnego raportu (do następnego zawodnika).
* Poprzedni raport (klawisz H) -- operacja odwrotna do Następnego raportu.
* Pokaż wszystko (strzałka w dół) -- natychmiast wyświetla wszystkie testy z aktualnego zadania, bez animacji.
* Schowaj wszystko (strzałka do góry) -- natychmiast chowa wszystkie testy z aktualnego zadania (aż do komentarzy, o ile istnieją) i **zatrzymuje prezentację**.
* Zatrzymaj (klawisz P) -- stopuje prezentację, można ją wznowić poprzez wykonanie dowolnego kroku.
* Przyspiesz (klawisz +) -- zwiększa prędkość prezentacji, zmiana prędkości prezentacji polega na przemnożeniu czasu wyświetlania testu/testów/komentarzy przez pewną stałą (czyli wszystkie te wartości równo się przeskalują), wskaźnikiem prędkości jest czarny pasek w prawym dolnym rogu).
* Zwolnij (klawisz -) -- zmniejsza prędkość prezentacji.


**Edytor**

W zakładce ``Ustawienia`` można ustawić:
* Czas na oglądanie komentarzy -- jest to czas, po którym komentarze zostaną schowane i zaczną się pokazywać testy, domyślna wartość to 3ms.
* Czas na oglądanie wyników testów -- na tyle czasu prezentacja zostanie zatrzymana po skończeniu wyświetlania testów z jednego zadania, domyślna wartość to 3s.
* Prędkość pokazywania testów -- jest to stała z przedziału [0, 1], przez którą zostanie przemnożony czas na pokazanie pojedynczego testu.
* Szacowany czas prezentacji -- czas po którym prezentacja powinna się zakończyć, nie licząc oczywiście czasu na jej **ręczne** zatrzymywanie i ewentualne cofanie. Z testów wynika, że czas ten może się różnieć o plus minus jedną minutę, ze względu na pewne opóźnienia, których nie da się przewidzieć.
* Metoda sortowania raportów -- po wybraniu funkcji sortującej, sortowanie wykonuje się **natychmiast** i powrót do opcji ``Brak sortowania`` nie cofnie tego. Definiowanie własnej funkcji sortującej jest opisane w oddzielnej sekcji.

Pozostałe zakładki odpowiadają poszczególnym zadaniom.
Z każdego zadania można wybrać dowolny podzbiór testów do pokazania, jak również wykluczyć całe zadanie z prezentacji.
Po dokonaniu zmian w tej zakładce, wskaźnik czasu w zakładce ``Ustawienia`` odpowiednio się zaktualizuje, biorąc pod uwagę tylko wymagany podzbiór testów/zadań.
Wyłączenie wszystkich testów i niewyłączenie zadania, powoduje pokazywanie komentarzy i pustej strony z testami.

Po dokonaniu zmian w ``Edytorze``, można zapisać prezentację do pliku, w postaci raportu XML, z dodatkowym polem ``<oipresentation></oipresentation>``, w którym znajdują się informacje o ustawieniach.
Wówczas zapisane będą jednie niezbędne informacje (wykluczone testy i zadania nie pojawią się w zapisanym raporcie).


Definiowanie własnej funkcji sortującej
=======================================
W katalogu ``src/Sort`` znajdują się pliki ``SortingFunctions.{cpp, h}``.

W pliku ``SortingFunctions.cpp`` należy umieścić definicję swojej funkcji sortującej.
Funkcja ta powinna przyjmować dwa wskaźniki na raporty i odpowiadać na pytanie: czy pierwszy raport powinien być ściśle przed raportem drugim?
Funkcja powinna być typu SortReportComparator, zdefiniowanego następująco

  typedef bool (*SortReportComparator)(const Report*, const Report*);

W pliku ``SortingFunctions.h`` należy zwiększyć licznik, mówiący o liczbie dostępnych funkcji sortujących,
a na samym dole w pliku ``SortingFunctions.cpp`` należy dopisać do tablicy wskaźnik na swoją funkcję.

Aby napisać funkcję sortującą, należy poznać klasę Report, której deklarację można znaleźć w pliku Report/Report.h
Można tam m.in. znaleźć metodę getContestant(), która zwraca wskaźnik na obiekt klasy, zawierającej wszystkie informacje o zawodniku.
Znowu, aby wydobyć te informacje, należy spojrzeć do pliku Report/Contestant.h i przeczytać co ta klasa udostępnia.
Klasa Report zawiera również informacje o wynikach zawodnika, więc można również sortować według takich kryteriów.
