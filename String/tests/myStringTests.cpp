#include <vector>
#include <algorithm>   // std::count_if
#include <type_traits> // std::is_same<>
#include <functional>  // std::bind2nd, std::not_equal_to
#include <cctype>      // isspace, isalpha, ...
#include <cstring>
#include <gtest/gtest.h>

#if __has_include("../mystring.h")
    #include "../mystring.h"
#elif __has_include("mystring.h")
    #include "mystring.h"
#else
    #error "File 'mystring.h' not found!"
#endif

namespace
{
using namespace std;
using namespace ::testing;
} // namespace


class MyStringTester : public ::testing::Test
{
};

TEST_F(MyStringTester, emptyStringConstruction_expectedSizeIsZero)
{
    const MyString text;
    EXPECT_EQ(0, text.size());
    EXPECT_EQ(MyString::initialBufferSize_+string().capacity(), text.capacity());
    EXPECT_TRUE(text.empty());
}

TEST_F(MyStringTester, constructionFromConstChar_expectedTextCopied)
{
    // source: https://pl.wikiquote.org/wiki/Stanis%C5%82aw_Michalkiewicz#O
    const char quote[] = "Oczywiscie te podwyzki podatkow to dla naszego dobra, "
                         "bo pieniadze, jak wiadomo, psuja charakter. "
                         "Im wiecej pieniedzy rzad nam skonfiskuje, tym lepiej dla nas. "
                         "Tak w kazdym razie mysla politycy, "
                         "ktorzy wprawdzie nieustannie pragna naszego dobra, "
                         "ale nam niestety juz coraz mniej go zostalo.";
    MyString text(quote);

    ASSERT_EQ(strlen(quote), text.size());
    EXPECT_FALSE(text.empty());
}

TEST_F(MyStringTester, clear_expectedEmptyStringAfterClearing)
{
    // source: Sw. Jan Pawel II
    const char quote[] = "Przyszlosc zaczyna sie dzisiaj, nie jutro";
    MyString text(quote);

    ASSERT_EQ(strlen(quote), text.size());
    EXPECT_FALSE(text.empty());

    text.clear();
    EXPECT_EQ(0, text.size());
    EXPECT_TRUE(text.empty());
}

TEST_F(MyStringTester, ostreamOperator_readTextShorterThanBufferSize_expectedTextInStream)
{
    ostringstream stream;
    const string textShorterThanInitialBufferSize(MyString::initialBufferSize_/2, 'i');
    const MyString text(textShorterThanInitialBufferSize.c_str());
    stream << text;
    ASSERT_EQ(textShorterThanInitialBufferSize, stream.str());
}

TEST_F(MyStringTester, ostreamOperator_readTextEqualToBufferSize_expectedTextInStream)
{
    ostringstream stream;
    const string textSizeEqualsInitialBufferSize(MyString::initialBufferSize_, 'j');
    const MyString text(textSizeEqualsInitialBufferSize.c_str());
    stream << text;
    ASSERT_EQ(textSizeEqualsInitialBufferSize, stream.str());
}

TEST_F(MyStringTester, ostreamOperator_readTextLongerThanBufferSize_expectedTextInStream)
{
    ostringstream stream;
    const string textLongerThanInitialBufferSize(MyString::initialBufferSize_*2, 'k');
    const MyString text(textLongerThanInitialBufferSize.c_str());
    stream << text;
    ASSERT_EQ(textLongerThanInitialBufferSize, stream.str());
}

TEST_F(MyStringTester, indexAccessOperator_expectedPossibilityToAccesElementsWithIndex)
{
    // source: http://www.cytat.eu/autorzy/albert-einstein/szalenstwem-jest-robic-wciaz-to-samo-i-oczekiwac-roznych-rezultatow/
    const char quote[] = "Szalenstwem jest robic wciaz to samo i oczekiwac roznych rezultatow.";
    const MyString text(quote);
    for (size_t i=0; quote[i]; ++i)
    {
        ASSERT_EQ(quote[i], text[i]) << "index = " << i;
    }
    ASSERT_THROW(text[text.size()+1], out_of_range);
}

TEST_F(MyStringTester, istreamOperator_expectedTextCopiedFromStreamToString)
{
    // source of quote: Sw. Antoni Pustelnik:
    const char quote[] = "Przyjda takie czasy, ze ludzie beda szaleni "
                         "i gdy zobacza kogos przy zdrowych zmyslach, "
                         "powstana przeciw niemu mowiac: "
                         "Jestes szalony bo nie jestes do nas podobny.";
    istringstream stream(quote);
    MyString text;
    stream >> text;
    for (size_t i=0; quote[i]; ++i)
    {
        ASSERT_EQ(quote[i], text[i]) << "index = " << i;
    }
}

// use: std::find_if_not, std::copy, ::isspace
TEST_F(MyStringTester, trimming_expectedSpacesRemoved)
{
    // source: https://www.cytaty.info/autor/terrypratchett-3.htm
    const char trimmedQuote[] = "Uniwersytety sa skarbnicami wiedzy: "
                                "studenci przychodza ze szkol przekonani, "
                                "ze wiedza juz prawie wszystko; po latach odchodza pewni, "
                                "ze nie wiedza praktycznie niczego. "
                                "Gdzie sie podziewa ta wiedza? Zostaje na uniwersytecie, "
                                "gdzie jest starannie suszona i skladana w magazynach.";
    {
        MyString text(trimmedQuote);
        text.trim();
        ASSERT_EQ(strlen(trimmedQuote), text.size());
    }
    {
        string textWithSpacesOnTheLeft = string(MyString::initialBufferSize_/4, ' ')
                + trimmedQuote;
        MyString text(textWithSpacesOnTheLeft.c_str());
        text.trim();
        ASSERT_EQ(strlen(trimmedQuote), text.size());
    }
    {
        string textWithMoreSpacesThanInitialSizeOnTheLeft = string(MyString::initialBufferSize_*2, ' ')
                + trimmedQuote;
        MyString text(textWithMoreSpacesThanInitialSizeOnTheLeft.c_str());
        text.trim();
        ASSERT_EQ(strlen(trimmedQuote), text.size());
    }
    {
        string textWithSpacesOnTheRight = trimmedQuote
                + string(MyString::initialBufferSize_*2, ' ');
        MyString text(textWithSpacesOnTheRight.c_str());
        text.trim();
        ASSERT_EQ(strlen(trimmedQuote), text.size());
    }
    {
        string textWithSpacesOnBothSidesTheRight = string(MyString::initialBufferSize_*2, ' ')
                + trimmedQuote
                + string(MyString::initialBufferSize_*2, ' ');
        MyString text(textWithSpacesOnBothSidesTheRight.c_str());
        text.trim();
        ASSERT_EQ(strlen(trimmedQuote), text.size());
    }
}

TEST_F(MyStringTester, operatorPlusEqual_expectedTextConcatenation)
{
    // source: http://cytatybaza.pl/cytat/jest-tylko-jedno-dobro-wiedza-i-jedno-zlo.html
    const char quote[] = "Jest tylko jedno dobro: wiedza, i jedno zlo: ignorancja";
    MyString text;
    for (size_t i=0; quote[i]; ++i)
    {
        text += quote[i];
    }
    ASSERT_EQ(strlen(quote), text.size());

    auto it = text.begin();
    for (size_t i=0; quote[i]; ++i)
    {
        EXPECT_EQ(quote[i], *it) << "position: " << i;
        ++it;
    }
}

// use: std::find_if, std::back_inserter, std::transform, ::tolower
TEST_F(MyStringTester, countingUniqueWords)
{
    // source of quote: Sienkiewicz:
    const char quote[] = "Lewice od prawicy rozni wszystko, "
                         "wlcznie ze stosunkiem do dzialan arytmetycznych: "
                         "Prawica lubi dodawac i mnozyc. "
                         "Lewica odejmowac i dzielic...po rowno!  ";
    MyString text(quote);
    constexpr size_t expectedNumberOfWords = 21; // all words 22 but "i" is twice
    const std::set<MyString> uniqueWords = text.getUniqueWords();
    ASSERT_EQ(expectedNumberOfWords, uniqueWords.size());
}

TEST_F(MyStringTester, countingWordsNumbersInText)
{
    // source of text below: https://poezja.org/wz/Ga%C5%82czy%C5%84ski_Ildefons_Konstanty/22823/Zaczarowana_doro%C5%BCka
    // removed polish letters with https://www.spolszcz.pl/usun-polskie-znaki.html
    // tolower with: https://convertcase.net/
    const char weddingPlay[] = R"DELIMITER(zapytajcie artura,
                                daje slowo: nie klamie,
                                ale bylo jak ulal
                                szesc slow w tym telegramie:
                                zaczarowana dorozka
                                zaczarowany dorozkarz
                                zaczarowany kon.

                                coz, wedlug ben alego,
                                czarnomistrza krakowa,
                                ,,to nie jest nic takiego
                                dorozke zaczarowac,

                                dosyc fiakrowi w oczy
                                blysnac specjalna broszka
                                i juzes zauroczyl
                                dorozkarza z dorozka

                                ale kon - nie." wiec dzwonie:
                                - serwus, to pan ben ali?
                                czy to mozliwe z koniem?
                                - nie, pana nabujali.
                                zadrzalem. druga w nocy.
                                pocztylion stal jak pika.
                                i urosly mi wlosy
                                do samego swiecznika:
                                zaczarowana dorozka?
                                zaczarowany dorozkarz?
                                zaczarowany kon?

                                niedobrze. serce. glowa.
                                w dodatku przez firanke:
                                srebrne dachy krakowa
                                jak ,,secundum joannem",

                                nizej gwiazdy i liscie
                                takie duze i male.
                                a moze rzeczywiscie
                                zgodzilem, zapomnialem?

                                moze chcialem za miasto?
                                czlowiek pragnie podrozy.
                                dryndziarz czekal i zasnal,
                                sen mu wasy wydluzyl
                                i go zaczarowali
                                wiatr i noc, i ben ali?
                                zaczarowana dorozka
                                zaczarowany dorozkarz
                                zaczarowany kon)DELIMITER";
    const MyString text(weddingPlay);
    const map<MyString,size_t> wordsUsage = text.countWordsUsageIgnoringCases();
    EXPECT_EQ(3, wordsUsage.at("zaczarowana")) << "all words: " << wordsUsage.size();
    EXPECT_EQ(6, wordsUsage.at("zaczarowany")) << "all words: " << wordsUsage.size();
    EXPECT_EQ(4, wordsUsage.at("kon")) << "all words: " << wordsUsage.size();
}

TEST_F(MyStringTester, countingWordsNumbersInTextIgnoringWordCases)
{
    // source of text below: https://www.planowaniewesela.pl/warto_wiedziec/zabawy_slubne_4.html
    const char weddingPlay[] = R"DELIMITER(Dawno, dawno temu zyli sobie krol z krolowa.
                               Mieli konie, karete i woznice.
                               Kiedys krol zawolal woznice i tak mu powiedzial:
                               "Woznico zaprzegaj konie do karety, bo krolowa chce pojechac na spacer".
                               Posluszny woznica poszedl i zapial konie do karety.
                               Kiedy krol z krolowa wsiedli do karety, krol zawolal:
                               "Woznico daj koniom znak do jazdy". I pojechali.
                               Para krolewska jedzie w swej pieknej karecie przez okolice,
                               nagle prawy kon okulal, lewemu koniowi nic sie nie stalo.
                               Przestraszony krol zawolal:
                               "Woznico, woznico, moj drogi woznico, sprawdz, co sie stalo".
                               Krolowa ze strachu zemdlala,
                               a woznica znalazl w kopycie prawego konia gwozdz
                               i go wyciagnal. W kopycie lewego konia nie znalazl nic.
                               Po chwili zniecierpliwiony krol zwraca sie z pytaniem do
                               woznicy: "Woznico, woznico, moj drogi woznico czy wszystko
                               w porzadku?" Woznica odpowiada ,ze tak.
                               Siada na kozle i daje koniom znak do jazdy.
                               Para krolewska w swej pieknej karecie,
                               zlotej karecie jedzie dalej.
                               Po chwili krol wychyla sie z okna karety i mowi do woznicy:
                               "Woznico, woznico, moj drogi woznico, zatrzymaj konie,
                               bo krolowa chce zaczerpnac swiezego powietrza".
                               Woznica zatrzymuje konie i kareta staje.
                               Z karety wysiada krol i krolowa.
                               Nagle w oddali slychac grzmot - zaczyna padac deszcz,
                               wszyscy sa mokrzy, nie ma co czekac
                               - krol zarzadza powrot na zamek.
                               Po przybyciu na zamek konie zatrzymuja sie i krol i krolowa
                               wysiadaja z karety. Krol wola do woznicy:
                               "Woznico, moj drogi woznico wyprzegnij konie i odstaw karete".
                               Zadowolona i szczesliwa krolowa pyta po chwili:
                               "Woznico czy odstawiles konie i karete?"
                               Woznica odpowiada, ze tak.)
                               "Dziekuje ci woznico, moj drogi woznico" - odpowiada krolowa. )DELIMITER";
    const MyString text(weddingPlay);
    const map<MyString,size_t> wordsUsage = text.countWordsUsageIgnoringCases();

    EXPECT_EQ(9, wordsUsage.at("krolowa")) << "all words: " << wordsUsage.size();
    EXPECT_EQ(16, wordsUsage.at("woznico")) << "all words: " << wordsUsage.size();
    EXPECT_EQ(11, wordsUsage.at("krol")) << "all words: " << wordsUsage.size();
}
// use: ::tolower, std::transform
TEST_F(MyStringTester, wordsIntoLowerCase)
{
    // source of quote: Izydor z Sewilii: https://pl.wikipedia.org/wiki/Izydor_z_Sewilli#Sentencje_z_dzie.C5.82_.C5.9Bw._Izydora
    const char quote[] = "Ucz sie, jak gdybys mial zyc wiecznie, zyj jak gdybys mial umrzec jutro";
    const char quoteLowerCase[] = "ucz sie, jak gdybys mial zyc wiecznie, zyj jak gdybys mial umrzec jutro";

    MyString text(quote);
    text.toLower();

    stringstream stream;
    stream << text;

    ASSERT_EQ(string(quoteLowerCase), stream.str());
}
// use: std::generate_n, std::back_inserter
TEST_F(MyStringTester, randomWordGeneration)
{
    constexpr size_t wordLength = 10;
    const auto randomWord = MyString::generateRandomWord(wordLength);
    ASSERT_EQ(wordLength, randomWord.size());
    for (size_t i=0; i<randomWord.size(); ++i)
    {
        EXPECT_TRUE(std::isalpha(randomWord[i])) << "index = " << i << ", word: " << randomWord;
    }
}
// use: std::search
TEST_F(MyStringTester, startsWith)
{
    // source of quote: Izydor z Sewilii: https://pl.wikipedia.org/wiki/Izydor_z_Sewilli#Sentencje_z_dzie.C5.82_.C5.9Bw._Izydora
    const char quote[] = "Nauczania powinny sie odznaczac poprawnoscia, prostota, otwartoscia, "
                         "powaga i skromnoscia, dalej: taktem i wdziekiem. "
                         "Do kazdego trzeba przemawiac indywidualnie, "
                         "w zaleznosci od jego stanu i poziomu moralnego. "
                         "A wiec kaznodzieja powinien wprzod przemyslec, co ma mowic, "
                         "do kogo, kiedy i w jaki sposob.";

    const MyString text(quote);
    EXPECT_TRUE(text.startsWith("Nauczania"));
    EXPECT_FALSE(text.startsWith("Oduczanie"));
}
// use: std::search
TEST_F(MyStringTester, endsWith)
{
    // source of quote: Izydor z Sewilii: https://pl.wikipedia.org/wiki/Izydor_z_Sewilli#Sentencje_z_dzie.C5.82_.C5.9Bw._Izydora
    const char quote[] = "Niesprawiedliwy to ktos, kto zle uzywa swoich dobr, "
                         "albo uzurpuje sobie cudze dobra, albo do tego co posiada, "
                         "doszedl w sposob niesprawiedliwy.";

    const MyString text(quote);
    EXPECT_TRUE(text.endsWith("sprawiedliwy."));
    EXPECT_FALSE(text.endsWith("lajdacki"));
}
// use: std::mismatch
TEST_F(MyStringTester, comparingTexts)
{
    // source of quote: Jan Pawel II Wielki: http://wolnosciowecytaty.blogspot.com/2017/07/jan-pawe-ii.html
    const char quote[] = "Wydaje sie, ze zarowno wewnatrz poszczegolnych narodow, "
                         "jak i w relacjach miedzynarodowych wolny rynek jest najbardziej "
                         "skutecznym narzedziem wykorzystania zasobow i zaspokajania potrzeb.";
    /// na koncu nie ma kropki:
    const char differentQuote[] = "Wydaje sie, ze zarowno wewnatrz poszczegolnych narodow, "
                         "jak i w relacjach miedzynarodowych wolny rynek jest najbardziej "
                         "skutecznym narzedziem wykorzystania zasobow i zaspokajania potrzeb";
    const MyString text1(quote), text2(quote), text3(differentQuote);

    ASSERT_EQ(text1, text2);
    ASSERT_NE(text1, text3);
    ASSERT_NE(text2, text3);
}
// use: std::copy, std::back_inserter
TEST_F(MyStringTester, joiningContainer)
{
    const MyString separator = ", ";
    const vector<MyString> polishExtinctAnimals =
    {
        "tarpan", "tur",  "drop zwyczajny", "jaszczurka zielona", "jesiotr zachodni",
        "karliczka zwyczajna", "norka europejska", "pustuleczka", "sep plowy", "strepet",
        "susel moregowany", "brodawnica", "mrowkolew drzewny", "pazurecznik wielki"
    };
    const MyString polishExtinctAnimalsAsString = "tarpan, tur, drop zwyczajny, jaszczurka zielona, "
                                                  "jesiotr zachodni, karliczka zwyczajna, "
                                                  "norka europejska, pustuleczka, sep plowy, "
                                                  "strepet, susel moregowany, brodawnica, "
                                                  "mrowkolew drzewny, pazurecznik wielki";
    const MyString joinedText = separator.join(polishExtinctAnimals);
    ASSERT_EQ(polishExtinctAnimalsAsString, joinedText);
}

// use: std::all_of
TEST_F(MyStringTester, all_of)
{
    const MyString onlyNumbers("03579");
    EXPECT_TRUE(onlyNumbers.all_of(::isdigit));
    EXPECT_TRUE(onlyNumbers.all_of(::isalnum));
    EXPECT_FALSE(onlyNumbers.all_of(::isalpha));
    EXPECT_FALSE(onlyNumbers.all_of(::isspace));
}
