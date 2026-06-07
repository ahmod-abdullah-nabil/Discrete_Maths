BEGIN
  READ n
  READ n×n matrix of 0s and 1s

  FUNCTION isReflexive:
      FOR each i: IF matrix[i][i] ≠ 1 RETURN false
      RETURN true

  FUNCTION isIrreflexive:
      FOR each i: IF matrix[i][i] ≠ 0 RETURN false
      RETURN true

  FUNCTION isSymmetric:
      FOR each i, j: IF matrix[i][j] ≠ matrix[j][i] RETURN false
      RETURN true

  FUNCTION isAntisymmetric:
      FOR each i ≠ j: 
          IF matrix[i][j] = 1 AND matrix[j][i] = 1 RETURN false
      RETURN true

  FUNCTION isTransitive:
      FOR each i, j, k:
          IF matrix[i][j] = 1 AND matrix[j][k] = 1 AND matrix[i][k] = 0
              RETURN false
      RETURN true

  PRINT results of all functions
END
