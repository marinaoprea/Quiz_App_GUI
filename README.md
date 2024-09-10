<h3> Overview </h3>
<p>
    Current program proposes a solution for a simple but custom dictionary-type application. Aim of the application is to help user memorize new words.
</p>
<p>
    The app acts like a storing place for new words and their meaning, both introduced by the user; moreover, app creates randomized quizez with the introduced words and keeps track of how many times a word has been answered correctly. When a word is considered to have been learned, it is erased from app's database.
</p>

<p>
    In order for it to be user friendly, a simple GUI was implemented.
</p>

<h3> Database </h3>
<p>
    Words are stored in a file with the filename pointed by <i>DATABASE_PATH</i>, which is by default <i><b>database.txt</i></b>.<br>
    Moreover, when app is launched, the contents of the same file are loaded into the program's memory.
</p>

<p>
    Data was stored in <i><b>json</i></b> format and therefore <b><i>nlohmann</b></i> library was used throughout the code.
</p>
<p>
    Inside the program, the database was loaded as a <i>std::set</i> with the comparison criterium being the introduced word. Thus, word-meaning pairs are stored in a sorted manner.
</p>

<h3>Manipulation operations</h3>
<p>
    New entries can be added or deleted. Moreover, a word can be searched in the database.
</p>
<p>
    Set usage assures a fast implementation of these operations.
</p>

<p>
    In order for additions and deletions to be persistent, <i>Save</i> operation should be performed or window should be closed (then Save is performed by default).
</p>

<h3>Search operation</h3>
<p>
    Search operation first searches for a perfect match. If
not found, suggestions are sought. Words containing given string are the suggestions considered.
</p>

<h3>Quiz operations </h3>
<p> Besides the word itself and its meaning, a new field was introduced, that is the number of times the word should be further correctly answered in order for it to be considered learned. <br>
    At first, a default number of "lives" is set and it decreases as the word is ansewered correctly inside a quiz operation. <br>
    However, when a word is considered ready to be deleted, the user is asked if the operation should be performed, in order to give the possibility of still maintaining it in the database.
</p>

<p> For quizes to work, there should be at least as many words introduced as the number of questions in the quiz. <br>
    Quiz questions are loaded statically as the quiz is requested and therefore changes produced by itself on the database are not taken into consideration.
<p>

<p> There are 2 types of quizes, normal quiz and multiple choice quiz.<br>
    For the multiple choice, random meanings are taken as choices for every question. <br>
    This quiz is easier than the normal one, where the requested meaning from the user, as quiz answer, should be precise in order to be considered correct. If the answer is at a <i>levenstein</i> distance of at most 5 characters (5 characters that are different or that are missing), warning is given and a new try is offered.
</p>

<p>
    Time taken for solving is measured and printed at the end for each quiz taken.
</p> 

<h4>Technical details</h4>
<p>
    Set elements are immutable in C++; thus, in order for number of lives to be modifiable, <i>short int *</i> was used (pointer is constant, value pointed at is modifiable).
</p>

<p>
    For obtaining quiz questions, randomized indexes were produced. However, for accessing elements at given index, set could not have been used. <br>
    Thus, a vector copy of the set is performed. In order to minimize copying operations, the addresses of the set elements were introduced in the vector, that is shallow copying was used.
</p>

<p>
    Random indexes were chosen using a uniform distribution, that is number of lives of a word is irrelevant.
</p>

<p>
    For time measurement <i>chrono::steady_clock</i> was used, that is monotonic clock that only counts increasingly.
</p>

<p>
    Levenstein distance can be easily calculated using dynamic programming.
</p>

<h3>GUI</h3>
<p>
    For GUI implementation, the cross-platform library <i><b>wxWidgets</i></b> has been used. <br>
    The main frame represents a simple menu, where the user can choose what operation to be performed. <br>
    Then, for each individual operation, a new frame was defined to provide its functionality.
</p>

<p>
    Buttons have been used as event handlers throughout the solution, but also <i>Enter</i> can be processed in order to ease word introduction. <br>
    By using <i>wxPanel</i> on each frame, tab navigation was provided.
</p>

<p>
    Adaptive layouts were used on every frame, in order for the windows to be aligned decently despite resize operations. <br>
    <i>Wx sizers</i> were used in order for the application to maintain constant appearance cross-platform.
</p>

<h3> Configuration </h3>
<p>
    Default configurations are in <i>constants.h</i> file. <br>
    A file named <i>database.txt</i> shall exist in the project directory for the app to launch in the default manner.
</p>

<h3> Requirements </h3>
<p> <b>wxWidgets installation and configuration</b> </p>
