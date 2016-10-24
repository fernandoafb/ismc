# ISMC - Incredibly Simple Model Checker

This tool is an attempt to build a model checker from the ground up in C. Unfortunately, it does not quite work with large instances.

It uses the [http://buddy.sourceforge.net/manual/main.html](BuDDy) library to manage the [https://en.wikipedia.org/wiki/Binary_decision_diagram](BDD), which is the main data structure for [https://en.wikipedia.org/wiki/Model_checking](model checking). The ISMC grammar for the input models and property specification is largely based on a subset of the commands in [NuSMV](http://nusmv.fbk.eu/)'s grammar.

Two other developers (Igor Rafael and Gabriel Quadros) contributed to this project much more than me, so thank you guys.

Historical note: this was developed as part of the credit requirements for my Master's in UFMG. I would like to thank Sérgio Campos for his [http://homepages.dcc.ufmg.br/~scampos/cursos/verificacao/](class) for providing this challenge to us which eventually turned into the main subject of my thesis.
