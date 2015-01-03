A simple implementation of Regex in c++
Supports: -    + * ? | operators
          - [] & () & [^] groups
          - repetitions
          - '.', \\d, \\D, \\w, \\W, \\s, \\S & [:...:] patterns
          - repetitions {a}, {a,}, {a, b}
          - $ & ^ operators
Use of Fhompson algorithm -> NO BACKREFERENCE!



Create a regex by creating a regex instance
Use 'find' or 'match' functions to match a string
