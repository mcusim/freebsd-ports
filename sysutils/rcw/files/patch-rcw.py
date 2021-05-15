--- rcw.py.orig	2021-05-15 12:40:48 UTC
+++ rcw.py
@@ -328,6 +328,34 @@ def build_pbi(lines):
             v2 = struct.pack(endianess + 'L', p2)
             subsection += v1
             subsection += v2
+        elif op == 'loadc':
+            if p1 == None or p2 == None:
+                print('Error: "loadc" instruction requires two parameters')
+                return ''
+            v1 = struct.pack(endianess + 'L', 0x80140000)
+            v2 = struct.pack(endianess + 'L', p1)
+            v3 = struct.pack(endianess + 'L', p2)
+            subsection += v1
+            subsection += v2
+            subsection += v3
+        elif op == 'jumpc':
+            if p1 == None or p2 == None:
+                print('Error: "jumpc" instruction requires two parameters')
+                return ''
+            v1 = struct.pack(endianess + 'L', 0x80850000)
+            v2 = struct.pack(endianess + 'L', p1)
+            v3 = struct.pack(endianess + 'L', p2)
+            subsection += v1
+            subsection += v2
+            subsection += v3
+        elif op == 'jump':
+            if p1 == None:
+                print('Error: "jump" instruction requires a parameter')
+                return ''
+            v1 = struct.pack(endianess + 'L', 0x80840000)
+            v2 = struct.pack(endianess + 'L', p1)
+            subsection += v1
+            subsection += v2
         elif op == 'awrite':
             if p1 == None or p2 == None:
                 print('Error: "awrite" instruction requires two parameters')
