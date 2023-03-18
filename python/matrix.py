import numpy as np
import scipy.linalg as la

# a=np.array([[1,2,3,0],[-2,3,6,-1],[-0.5,3.1,2,1.1]])
# print(a.shape)
# print(a)

# I=np.eye(3)
# print(I)
# print("________________________________________________________________")
# b=np.array([[1,2,3,0],[-2,3,6,-1],[-0.5,3.1,2,1.1],[0,1,-3,4]]);
# print(b)
# print(a@b)
# print((a@b).shape)

# def mat(A):
#     B=np.zeros((3,3));
#     for i in range(3):
#         for j in range(3):
#             if i==0:
#                 B[i,j]=A[i+1,j];
#             elif i==1:
#                  B[i,j]=A[i-1,j];
#             else:
#                 B[i,j]=3*A[0,j]+A[i,j];
#     return(B)

# print(mat(np.eye(3)))
# Define elementary matrices
def E1(n,c,i,j):
    E = np.eye(n)
    E[j, i] = c
    return E

def E2(n,i,j):
    E = np.eye(n)
    E[[i, j]] = E[[j, i]]
    return E

def E3(n,c,i):
    E = np.eye(n)
    E[i, i] = c
    return E

# Define row operations using elementary matrices
def replace_row(A, c, i, j):
    E = E1(A.shape[0], c, i, j)
    return E @ A

def switch_rows(A, i, j):
    E = E2(A.shape[0], i, j)
    return E @ A

def scale_row(A, c, i):
    E = E3(A.shape[0], c, i)
    return E @ A

# Apply row operations to matrix A to obtain reduced echelon form
A = np.array([[1, 0, 0, -2, -3],
              [0, 2, 2, 0, 0],
              [0, 0, 1, 3, 1],
              [-2, 3, 2, 5, 1]])

print("Original matrix A:\n", A)

A = replace_row(A, 2, 0, 3)
print("step 1:After R4 <- R4 + 2R1:\n", A)

A = scale_row(A, 1/2, 1)
print("step 1.2: After R2 <-(1/2)R2:\n", A)

A = replace_row(A, -3, 1, 3)
print("step 2:After R4 <- R4 - 3R2:\n", A)

A = replace_row(A, -1, 2, 1)
print("step 3: After R2 <- R2 - R3:\n", A)

A = replace_row(A, 1, 2, 3)
print("step 4: After R4 <- R4 + R3:\n", A)

A = scale_row(A, 1/4, 3)
print("step 5: After R4 <- (1/4)R4:\n", A)

A = replace_row(A, 2, 3,0)
print("step 6:After R1 <- R1 + 2R4:\n", A)

A = replace_row(A, 3, 3, 1)
print("step 7:After R2 <- R2 + 3R4:\n", A)

A = replace_row(A, -3, 3, 2)
print("step 8:After R3 <- R3 - 3R4:\n", A)

print("Reduced echelon form of A:\n", A)


B = np.array([[1,-2,3,0],[-2,4,-6,0],[0,1,-1,0]])
print("\n\n\noriginal augmented matrix\n",B)
B = replace_row(B, 2, 0, 1 )
print("R2<-R2 + 2R1\n",B)
B = replace_row(B,2,2,0)
print("R1<-R1 + 2R3\n",B)

print("Final result:\n",B)




        
# Check if there are any rows of zeros in the reduced row echelon form
if np.any(np.all(B[:, :-1] == 0, axis=1)):
    print("The vectors in B are linearly dependent.")
else:
    print("The vectors in B are linearly independent.")