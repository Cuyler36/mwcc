"""Exercise same-basename dependency files across concurrent compiler processes."""
from pathlib import Path
import subprocess
import sys
from tempfile import TemporaryDirectory
import unittest


class CompilerDependencyTests(unittest.TestCase):
    def test_colliding_dependency_files_keep_their_own_source(self):
        tools = Path(__file__).resolve().parent
        temp_parent = tools.parent / 'build'
        temp_parent.mkdir(exist_ok=True)
        with TemporaryDirectory(dir=temp_parent) as directory:
            root = Path(directory).resolve()
            self.assertTrue(root.is_relative_to(temp_parent.resolve()))
            (root / 'tools').mkdir()
            (root / 'tools/transform_dep.py').write_bytes((tools / 'transform_dep.py').read_bytes())
            fake = root / 'fake_compiler.py'
            fake.write_text(
                "from pathlib import Path\nimport sys,time\n"
                "Path('same.dep').write_text('same.obj: '+sys.argv[1]+'\\n')\n"
                "time.sleep(0.15)\n"
            )
            jobs = [subprocess.Popen([
                sys.executable, str(tools / 'run_compiler.py'), '--dep', 'same.dep',
                '--out', name + '.obj', '--', sys.executable, str(fake), name + '.c',
            ], cwd=root, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
                for name in ['first', 'second']]
            for job in jobs:
                stdout, stderr = job.communicate(timeout=30)
                self.assertEqual(job.returncode, 0, stdout + stderr)
            for name in ['first', 'second']:
                self.assertEqual((root / (name + '.obj.d')).read_text(),
                                 f'{name}.obj: {name}.c\n')
            self.assertFalse((root / 'same.dep').exists())


if __name__ == '__main__':
    unittest.main()
