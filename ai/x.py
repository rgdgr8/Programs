class Solution:
    #User function Template for python3

    # arr[]: Input Array
    # N : Size of the Array arr[]
    #Function to count inversions in the array.
    def inversionCount(self, arr, n):
        c = 0
        def merge(l,m,r):
            nonlocal c
            a1 = arr[l:m+1]
            sz1 = len(a1)
            a2 = arr[m+1:r+1]
            sz2 = len(a2)
            i,j,k = 0,0,l
            while(i<sz1 and j<sz2):
                if(a1[i]<=a2[j]):
                    arr[k] = a1[i]
                    i += 1
                else:
                    arr[k] = a2[j]
                    j += 1
                    c += (sz1-i)
                k += 1

            while(i<sz1):
                arr[k] = a1[i]
                k += 1
                i += 1
                #c += 1
            while(j<sz2):
                arr[k] = a2[j]
                k += 1
                j += 1
            print(arr,c)

        def part(l,r):
            if(l<r):
                m = (l+r)//2
                part(l,m)
                part(m+1,r)
                merge(l,m,r)

        part(0,n-1)
        print(arr)
        return c

if __name__=='__main__':
    t = 1
    for tt in range(t):
        n = int(input())
        a = list(map(int, input().strip().split()))
        obj = Solution()
        print(obj.inversionCount(a,n))
