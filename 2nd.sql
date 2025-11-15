Start
    Display program introduction and choose input mode (1 or 2)

    Initialize:
        have_value ← false
        max_val ← 0
        max_pos ← 0
        count ← 0

    IF mode = 1 THEN           // Fixed count mode
        Read n
        FOR i ← 1 TO n DO
            Prompt user for element i
            IF input is invalid THEN
                Display error and re-enter value
            ELSE
                count ← count + 1
                IF have_value = false OR value > max_val THEN
                    max_val ← value
                    max_pos ← count
                    have_value ← true
                ENDIF
            ENDIF
        ENDFOR

    ELSE IF mode = 2 THEN      // Free entry mode
        REPEAT
            Prompt user for number or "done"
            IF input = "done" THEN
                EXIT loop
            ELSE IF input is valid number THEN
                count ← count + 1
                IF have_value = false OR value > max_val THEN
                    max_val ← value
                    max_pos ← count
                    have_value ← true
                ENDIF
            ELSE
                Display error
            ENDIF
        UNTIL user finishes input
    ENDIF

    IF have_value = true THEN
        Display count, max_val, and max_pos
    ELSE
        Display "No valid numbers entered"
    ENDIF
Stop
