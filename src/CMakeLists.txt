set (SOURCES
	main.cpp
	MainWindow.cpp

	Parser/XmlReader.cpp
	Parser/TasksReader.cpp
	Parser/ResultsReader.cpp
	Parser/OptionsReader.cpp

	Report/Report.cpp
	Report/TimeInt.cpp

	Report/Tests.cpp
	Report/Test.cpp
	Report/TestGroup.cpp
	Report/Task.cpp

	Report/TestsResult.cpp
	Report/TestResult.cpp
	Report/TestGroupResult.cpp
	Report/TaskResult.cpp

	Report/Contestant.cpp

	Presentation.cpp
	WritePresentation.cpp

	View/View.cpp
	View/ViewTable.cpp
	View/ViewTestGroup.cpp
	View/ViewTest.cpp
	View/ViewGroupPoints.cpp
	View/ViewComments.cpp
	View/ViewFrame.cpp
	View/SmallViews/ViewTestName.cpp
	View/SmallViews/ViewTestStatus.cpp
	View/SmallViews/ViewTestTime.cpp
	View/SmallViews/ViewTaskResult.cpp

	Editor/Editor.cpp
	Editor/TabsEditor.cpp
	Editor/TaskEditor.cpp
	Editor/OptionsEditor.cpp

	ScreenSwitch.cpp

	Sort/SortReports.cpp
	Sort/SortingFunctions.cpp
)

set (HEADERS
	main.h
	MainWindow.h

	Parser/XmlReader.h
	Parser/TasksReader.h
	Parser/ResultsReader.h
	Parser/OptionsReader.h

	Report/Report.h
	Report/TimeInt.h

	Report/Tests.h
	Report/Test.h
	Report/TestGroup.h
	Report/Task.h

	Report/TestsResult.h
	Report/TestResult.h
	Report/TestGroupResult.h
	Report/TaskResult.h

	Report/Contestant.h

	Presentation.h
	WritePresentation.h

	View/View.h
	View/ViewTable.h
	View/ViewTestGroup.h
	View/ViewTest.h
	View/ViewGroupPoints.h
	View/ViewComments.h
	View/ViewFrame.h
	View/SmallViews/ViewTestName.h
	View/SmallViews/ViewTestStatus.h
	View/SmallViews/ViewTestTime.h
	View/SmallViews/ViewTaskResult.h

	Editor/Editor.h
	Editor/TabsEditor.h
	Editor/TaskEditor.h
	Editor/OptionsEditor.h

	ScreenSwitch.h

	Sort/SortReports.h
	Sort/SortingFunctions.h

	QListConstPointerIterator.h
)

qt4_wrap_cpp (SOURCES ${HEADERS})

qt4_add_resources(SOURCES resources.qrc)

add_executable (program.e ${SOURCES})
target_link_libraries (program.e ${QT_LIBRARIES})
